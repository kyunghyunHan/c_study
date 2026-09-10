/*
 * tutorial01.c
 *
 * FFmpeg를 사용하여 동영상의 비디오 스트림을 디코딩하고,
 * 처음 5개의 프레임을 RGB24 형식으로 변환한 뒤
 * frame1.ppm ~ frame5.ppm 파일로 저장합니다.
 *
 * macOS + Homebrew FFmpeg 기준
 *
 * 설치:
 *   brew install ffmpeg pkg-config
 *
 * 컴파일:
 *   clang -Wall -Wextra -O2 tutorial01.c -o tutorial01 \
 *     $(pkg-config --cflags --libs \
 *       libavformat libavcodec libavutil libswscale)
 *
 * 실행:
 *   ./tutorial01 video.mp4
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * libavformat:
 * MP4, AVI, MOV, MKV 등의 컨테이너 파일을 열고
 * 내부 스트림과 패킷을 읽는 기능을 제공합니다.
 */
#include <libavformat/avformat.h>

/*
 * libavcodec:
 * H.264, HEVC, VP9 등의 코덱을 디코딩하는 기능을 제공합니다.
 */
#include <libavcodec/avcodec.h>

/*
 * av_strerror(), AVERROR_EOF 등의 유틸리티가 들어 있습니다.
 */
#include <libavutil/error.h>

/*
 * av_frame_alloc(), AVFrame 관련 기능입니다.
 */
#include <libavutil/frame.h>

/*
 * av_image_alloc() 등 이미지 버퍼 관련 기능입니다.
 */
#include <libavutil/imgutils.h>

/*
 * 픽셀 형식을 변환합니다.
 * 예: YUV420P → RGB24
 */
#include <libswscale/swscale.h>

/*
 * FFmpeg 오류 코드를 사람이 읽을 수 있는 문자열로 출력합니다.
 */
static void print_ffmpeg_error(const char *message, int error_code)
{
    char error_buffer[AV_ERROR_MAX_STRING_SIZE];

    av_strerror(
        error_code,
        error_buffer,
        sizeof(error_buffer)
    );

    fprintf(
        stderr,
        "%s: %s\n",
        message,
        error_buffer
    );
}

/*
 * RGB24 AVFrame을 PPM 이미지로 저장합니다.
 *
 * PPM P6 형식:
 *
 * P6
 * 가로 세로
 * 255
 * RGB 바이너리 데이터
 *
 * 예:
 * P6
 * 1920 1080
 * 255
 * [RGB 데이터...]
 */
static int save_frame_as_ppm(
    const AVFrame *frame,
    int width,
    int height,
    int frame_number
)
{
    char filename[64];

    /*
     * frame1.ppm, frame2.ppm 등의 파일명을 만듭니다.
     */
    int written = snprintf(
        filename,
        sizeof(filename),
        "frame%d.ppm",
        frame_number
    );

    if (written < 0 || written >= (int)sizeof(filename)) {
        fprintf(stderr, "파일 이름 생성에 실패했습니다.\n");
        return -1;
    }

    /*
     * PPM은 바이너리 데이터이므로 "wb" 모드로 엽니다.
     */
    FILE *file = fopen(filename, "wb");

    if (file == NULL) {
        perror("PPM 파일을 열 수 없습니다");
        return -1;
    }

    /*
     * PPM 헤더를 기록합니다.
     *
     * P6   : 바이너리 RGB 형식
     * width height
     * 255  : 각 색상 채널의 최댓값
     */
    if (fprintf(
            file,
            "P6\n%d %d\n255\n",
            width,
            height
        ) < 0) {
        fprintf(stderr, "PPM 헤더 작성에 실패했습니다.\n");
        fclose(file);
        return -1;
    }

    /*
     * RGB24는 한 픽셀당 3바이트입니다.
     *
     * R: 1바이트
     * G: 1바이트
     * B: 1바이트
     *
     * linesize[0]에는 각 이미지 행의 실제 메모리 간격이 들어갑니다.
     * 메모리 정렬 때문에 width * 3보다 클 수 있으므로,
     * 다음 행으로 이동할 때 반드시 linesize를 사용해야 합니다.
     */
    for (int y = 0; y < height; y++) {
        const uint8_t *row =
            frame->data[0] +
            (size_t)y * frame->linesize[0];

        size_t bytes_to_write = (size_t)width * 3;

        size_t bytes_written = fwrite(
            row,
            1,
            bytes_to_write,
            file
        );

        if (bytes_written != bytes_to_write) {
            fprintf(
                stderr,
                "%s의 픽셀 데이터 작성에 실패했습니다.\n",
                filename
            );

            fclose(file);
            return -1;
        }
    }

    if (fclose(file) != 0) {
        perror("PPM 파일 닫기 실패");
        return -1;
    }

    printf("저장 완료: %s\n", filename);

    return 0;
}

/*
 * 디코더에서 현재 받을 수 있는 프레임을 모두 꺼냅니다.
 *
 * avcodec_send_packet():
 *   압축된 패킷을 디코더에 전달합니다.
 *
 * avcodec_receive_frame():
 *   디코딩이 완료된 원시 프레임을 가져옵니다.
 *
 * 하나의 패킷에서 프레임이 여러 개 나올 수도 있으므로,
 * receive_frame()을 반복 호출해야 합니다.
 */
static int receive_and_save_frames(
    AVCodecContext *codec_context,
    AVFrame *decoded_frame,
    AVFrame *rgb_frame,
    struct SwsContext *sws_context,
    int *saved_frame_count,
    int maximum_frames
)
{
    while (*saved_frame_count < maximum_frames) {
        /*
         * 디코더에서 완성된 프레임 하나를 가져옵니다.
         */
        int result = avcodec_receive_frame(
            codec_context,
            decoded_frame
        );

        /*
         * EAGAIN:
         * 현재는 출력할 프레임이 없으며,
         * 다음 패킷을 보내야 한다는 뜻입니다.
         */
        if (result == AVERROR(EAGAIN)) {
            return 0;
        }

        /*
         * EOF:
         * 디코더가 완전히 비워졌고
         * 더 이상 출력할 프레임이 없다는 뜻입니다.
         */
        if (result == AVERROR_EOF) {
            return 1;
        }

        if (result < 0) {
            print_ffmpeg_error(
                "비디오 프레임 디코딩 실패",
                result
            );

            return result;
        }

        /*
         * 디코딩된 프레임의 픽셀 형식은 보통
         * YUV420P, NV12, YUV422P 등입니다.
         *
         * PPM 파일에 저장하기 위해 RGB24로 변환합니다.
         */
        int scaled_height = sws_scale(
            sws_context,

            /*
             * 원본 이미지 데이터 배열입니다.
             * YUV라면 Y, U, V 평면이 각각 다른 data 항목에
             * 저장될 수 있습니다.
             */
            (const uint8_t *const *)decoded_frame->data,

            /*
             * 원본 각 평면의 한 행 크기입니다.
             */
            decoded_frame->linesize,

            /*
             * 변환을 시작할 원본 이미지의 Y 좌표입니다.
             */
            0,

            /*
             * 변환할 행 수입니다.
             */
            codec_context->height,

            /*
             * 변환 결과가 저장될 RGB 프레임입니다.
             */
            rgb_frame->data,
            rgb_frame->linesize
        );

        if (scaled_height <= 0) {
            fprintf(
                stderr,
                "RGB 변환에 실패했습니다.\n"
            );

            av_frame_unref(decoded_frame);
            return -1;
        }

        (*saved_frame_count)++;

        if (save_frame_as_ppm(
                rgb_frame,
                codec_context->width,
                codec_context->height,
                *saved_frame_count
            ) != 0) {
            av_frame_unref(decoded_frame);
            return -1;
        }

        /*
         * AVFrame 구조체는 재사용합니다.
         * 현재 프레임이 참조하는 내부 버퍼만 해제합니다.
         */
        av_frame_unref(decoded_frame);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    /*
     * 프로그램 실행 시 동영상 경로가 필요합니다.
     *
     * 예:
     * ./tutorial01 video.mp4
     */
    if (argc != 2) {
        fprintf(
            stderr,
            "사용법: %s <동영상 파일>\n",
            argv[0]
        );

        fprintf(
            stderr,
            "예시: %s video.mp4\n",
            argv[0]
        );

        return EXIT_FAILURE;
    }

    const char *input_filename = argv[1];

    /*
     * 각 FFmpeg 객체를 NULL로 초기화합니다.
     * cleanup 영역에서 NULL인지 안전하게 확인할 수 있습니다.
     */
    AVFormatContext *format_context = NULL;
    AVCodecContext *codec_context = NULL;

    const AVCodec *decoder = NULL;

    AVPacket *packet = NULL;
    AVFrame *decoded_frame = NULL;
    AVFrame *rgb_frame = NULL;

    struct SwsContext *sws_context = NULL;

    int video_stream_index = -1;
    int saved_frame_count = 0;
    int exit_status = EXIT_FAILURE;
    int result = 0;

    const int maximum_frames = 5;

    /*
     * 1. 입력 파일 열기
     *
     * libavformat이 파일 확장자와 헤더를 검사하여
     * MP4, MOV, AVI 등의 컨테이너 형식을 자동으로 감지합니다.
     */
    result = avformat_open_input(
        &format_context,
        input_filename,
        NULL,
        NULL
    );

    if (result < 0) {
        print_ffmpeg_error(
            "동영상 파일을 열 수 없습니다",
            result
        );

        goto cleanup;
    }

    /*
     * 2. 스트림 정보 검색
     *
     * 파일 내부의 비디오, 오디오, 자막 스트림 정보를 읽습니다.
     */
    result = avformat_find_stream_info(
        format_context,
        NULL
    );

    if (result < 0) {
        print_ffmpeg_error(
            "스트림 정보를 찾을 수 없습니다",
            result
        );

        goto cleanup;
    }

    /*
     * 입력 파일 정보를 터미널에 출력합니다.
     *
     * 컨테이너 형식, 코덱, 해상도, 프레임률,
     * 오디오 정보 등을 확인할 수 있습니다.
     */
    av_dump_format(
        format_context,
        0,
        input_filename,
        0
    );

    /*
     * 3. 가장 적절한 비디오 스트림 찾기
     *
     * 파일에 비디오 스트림이 여러 개 있을 수 있으므로
     * FFmpeg가 기본으로 사용할 비디오 스트림을 선택하게 합니다.
     *
     * decoder 인수도 함께 전달하여 해당 스트림을 처리할
     * 디코더를 찾습니다.
     */
    video_stream_index = av_find_best_stream(
        format_context,
        AVMEDIA_TYPE_VIDEO,
        -1,
        -1,
        &decoder,
        0
    );

    if (video_stream_index < 0) {
        print_ffmpeg_error(
            "비디오 스트림을 찾을 수 없습니다",
            video_stream_index
        );

        goto cleanup;
    }

    if (decoder == NULL) {
        fprintf(
            stderr,
            "비디오 디코더를 찾을 수 없습니다.\n"
        );

        goto cleanup;
    }

    AVStream *video_stream =
        format_context->streams[video_stream_index];

    printf(
        "\n비디오 스트림 번호: %d\n",
        video_stream_index
    );

    printf(
        "디코더: %s\n",
        decoder->name
    );

    /*
     * 4. 디코더 컨텍스트 생성
     *
     * AVCodecContext는 현재 디코딩 작업에 필요한
     * 코덱 설정과 상태를 보관합니다.
     */
    codec_context = avcodec_alloc_context3(decoder);

    if (codec_context == NULL) {
        fprintf(
            stderr,
            "코덱 컨텍스트 메모리 할당에 실패했습니다.\n"
        );

        goto cleanup;
    }

    /*
     * 5. 스트림의 코덱 파라미터를 디코더 컨텍스트로 복사
     *
     * 예전 튜토리얼의:
     *
     *   stream->codec
     *   avcodec_copy_context()
     *
     * 대신 현재 API에서는:
     *
     *   stream->codecpar
     *   avcodec_parameters_to_context()
     *
     * 를 사용합니다.
     */
    result = avcodec_parameters_to_context(
        codec_context,
        video_stream->codecpar
    );

    if (result < 0) {
        print_ffmpeg_error(
            "코덱 파라미터 복사 실패",
            result
        );

        goto cleanup;
    }

    /*
     * 6. 디코더 열기
     */
    result = avcodec_open2(
        codec_context,
        decoder,
        NULL
    );

    if (result < 0) {
        print_ffmpeg_error(
            "비디오 디코더를 열 수 없습니다",
            result
        );

        goto cleanup;
    }

    printf(
        "해상도: %d x %d\n",
        codec_context->width,
        codec_context->height
    );

    printf(
        "원본 픽셀 형식 번호: %d\n\n",
        codec_context->pix_fmt
    );

    /*
     * 해상도가 정상인지 확인합니다.
     */
    if (codec_context->width <= 0 ||
        codec_context->height <= 0) {
        fprintf(
            stderr,
            "잘못된 비디오 해상도입니다: %d x %d\n",
            codec_context->width,
            codec_context->height
        );

        goto cleanup;
    }

    /*
     * 7. 패킷 및 프레임 객체 생성
     *
     * packet:
     *   컨테이너에서 읽은 압축 데이터
     *
     * decoded_frame:
     *   디코더가 출력한 원본 픽셀 형식의 프레임
     *
     * rgb_frame:
     *   RGB24로 변환된 프레임
     */
    packet = av_packet_alloc();
    decoded_frame = av_frame_alloc();
    rgb_frame = av_frame_alloc();

    if (packet == NULL ||
        decoded_frame == NULL ||
        rgb_frame == NULL) {
        fprintf(
            stderr,
            "패킷 또는 프레임 메모리 할당에 실패했습니다.\n"
        );

        goto cleanup;
    }

    /*
     * 8. RGB 프레임 정보 설정
     */
    rgb_frame->format = AV_PIX_FMT_RGB24;
    rgb_frame->width = codec_context->width;
    rgb_frame->height = codec_context->height;

    /*
     * RGB 이미지 버퍼를 할당합니다.
     *
     * 정렬값 1:
     * PPM에 width * 3바이트씩 쓰기 쉽게 최소 정렬을 사용합니다.
     *
     * 성공하면 rgb_frame->data와 linesize가 설정됩니다.
     */
    result = av_image_alloc(
        rgb_frame->data,
        rgb_frame->linesize,
        rgb_frame->width,
        rgb_frame->height,
        AV_PIX_FMT_RGB24,
        1
    );

    if (result < 0) {
        print_ffmpeg_error(
            "RGB 이미지 버퍼 할당 실패",
            result
        );

        goto cleanup;
    }

    /*
     * 9. 픽셀 형식 변환 컨텍스트 생성
     *
     * 입력:
     *   동영상 원본 크기와 픽셀 형식
     *
     * 출력:
     *   동일한 크기의 RGB24
     *
     * SWS_BILINEAR:
     *   크기 변환이 필요한 경우 bilinear 알고리즘을 사용합니다.
     *   여기서는 크기가 같아 주로 색상 형식 변환에 사용됩니다.
     */
    sws_context = sws_getContext(
        codec_context->width,
        codec_context->height,
        codec_context->pix_fmt,

        codec_context->width,
        codec_context->height,
        AV_PIX_FMT_RGB24,

        SWS_BILINEAR,

        NULL,
        NULL,
        NULL
    );

    if (sws_context == NULL) {
        fprintf(
            stderr,
            "SwsContext 생성에 실패했습니다.\n"
        );

        goto cleanup;
    }

    /*
     * 10. 파일에서 패킷을 반복해서 읽습니다.
     */
    while (
        saved_frame_count < maximum_frames &&
        av_read_frame(format_context, packet) >= 0
    ) {
        /*
         * 현재 패킷이 우리가 찾은 비디오 스트림에
         * 속하는지 확인합니다.
         *
         * 오디오나 자막 패킷은 무시합니다.
         */
        if (packet->stream_index == video_stream_index) {
            /*
             * 압축된 패킷을 디코더에 전달합니다.
             */
            result = avcodec_send_packet(
                codec_context,
                packet
            );

            if (result < 0) {
                print_ffmpeg_error(
                    "패킷을 디코더에 전달하지 못했습니다",
                    result
                );

                /*
                 * 현재 패킷의 내부 데이터 참조를 해제합니다.
                 */
                av_packet_unref(packet);
                goto cleanup;
            }

            /*
             * 하나의 패킷에서 여러 프레임이 나올 수 있으므로,
             * 받을 수 있는 프레임을 모두 가져옵니다.
             */
            result = receive_and_save_frames(
                codec_context,
                decoded_frame,
                rgb_frame,
                sws_context,
                &saved_frame_count,
                maximum_frames
            );

            if (result < 0) {
                av_packet_unref(packet);
                goto cleanup;
            }
        }

        /*
         * av_read_frame()이 채운 패킷 내부 데이터 참조를
         * 다음 반복 전에 해제합니다.
         *
         * AVPacket 구조체 자체는 계속 재사용합니다.
         */
        av_packet_unref(packet);
    }

    /*
     * 11. 디코더 플러시
     *
     * B-frame처럼 디코더 내부에 지연되어 남아 있는 프레임이
     * 있을 수 있습니다.
     *
     * NULL 패킷을 보내면 더 이상 입력 데이터가 없다는 것을
     * 디코더에 알려 내부 프레임을 출력하게 합니다.
     */
    if (saved_frame_count < maximum_frames) {
        result = avcodec_send_packet(
            codec_context,
            NULL
        );

        if (result < 0 && result != AVERROR_EOF) {
            print_ffmpeg_error(
                "디코더 플러시 시작 실패",
                result
            );

            goto cleanup;
        }

        result = receive_and_save_frames(
            codec_context,
            decoded_frame,
            rgb_frame,
            sws_context,
            &saved_frame_count,
            maximum_frames
        );

        if (result < 0) {
            goto cleanup;
        }
    }

    printf(
        "\n총 %d개의 프레임을 저장했습니다.\n",
        saved_frame_count
    );

    if (saved_frame_count == 0) {
        fprintf(
            stderr,
            "디코딩된 비디오 프레임이 없습니다.\n"
        );

        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    /*
     * 12. 리소스 정리
     *
     * 할당 순서와 대체로 반대 순서로 해제합니다.
     */

    if (packet != NULL) {
        /*
         * 혹시 남아 있는 패킷 데이터 참조를 먼저 해제합니다.
         */
        av_packet_unref(packet);
        av_packet_free(&packet);
    }

    if (rgb_frame != NULL) {
        /*
         * av_image_alloc()으로 할당한 실제 이미지 버퍼입니다.
         *
         * rgb_frame->data[0]이 전체 버퍼의 시작 주소입니다.
         */
        av_freep(&rgb_frame->data[0]);
    }

    /*
     * AVFrame 구조체 자체를 해제합니다.
     */
    av_frame_free(&rgb_frame);
    av_frame_free(&decoded_frame);

    /*
     * 픽셀 형식 변환 컨텍스트를 해제합니다.
     */
    sws_freeContext(sws_context);

    /*
     * 디코더 컨텍스트를 닫고 메모리까지 해제합니다.
     *
     * 현재 API에서는 avcodec_close() 후 av_free()보다
     * avcodec_free_context()를 사용합니다.
     */
    avcodec_free_context(&codec_context);

    /*
     * 입력 파일과 AVFormatContext를 닫고 해제합니다.
     */
    avformat_close_input(&format_context);

    return exit_status;
}