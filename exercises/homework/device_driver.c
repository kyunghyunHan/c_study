/*
숙제 - C
가상 제어보드 디바이스 3개
콘솔에 명령 입력
led1 on, sw1 toggle, led2 status 등

포인터 개념
1. 함수 포인터 : DevHandler, handler(dev)
2. 배열 포인터 : int (*hist)[MAX_LOG]
3. 포인터 배열 : Device *devices[DEVICE_COUNT]
4. 구조체 포인터 : Device *dev
5. 주소 전달로 원본 수정 : change_state에서 (*dev).state 변경
*/
#include <stdio.h>
#include <string.h>
//max lgo5
#define MAX_LOG 5

#define DEVICE_COUNT 3
#define MAX_INPUT 128

// 처음에는 OFF
typedef enum
{
    DEV_OFF = 0,
    DEV_ON = 1
} DevState;

// 장치 하나의 정보
typedef struct Device
{
    char name[16];
    DevState state;
    int log[MAX_LOG];
    int log_count; // 기록 몇 개 있는지
} Device;

// int 반환하고 Device 주소 받는 함수 포인터 타입
typedef int (*DevHandler)(Device *dev);

// 명령 이름이랑 실행할 함수
typedef struct
{
    const char *cmd_name;
    DevHandler handler;
} Command;

/*함수들 

*/
int cmd_on(Device *dev);
int cmd_off(Device *dev);
int cmd_toggle(Device *dev);
//추력후 0반환해야함
int cmd_status(Device *dev);

// 명령어 배열
static const Command command_table[] = {
    {"on", cmd_on},
    {"off", cmd_off},
    {"toggle", cmd_toggle},
    {"status", cmd_status}};

// 상태를 문자열로
static const char *state_name(DevState state)
{
    return state == DEV_ON ? "ON" : "OFF";
}

// log가 가득 차면 오래된 것부터 버림
static void append_log(Device *dev, DevState state)
{
    if ((*dev).log_count == MAX_LOG)
    {
        // 한 칸씩 앞으로 당김
        for (int i = 1; i < MAX_LOG; ++i)
            (*dev).log[i - 1] = (*dev).log[i];

        --(*dev).log_count;
    }

    // 마지막에 새 상태 넣고 개수 증가
    (*dev).log[(*dev).log_count++] = (int)state;
}

static int change_state(Device *dev, DevState next)
{
    // 이미 같은 상태면 변경 안 함
    if ((*dev).state == next)
        return -1;

    DevState previous = (*dev).state;

    // 주소로 접근해서 원본 Device 수정
    (*dev).state = next;

    append_log(dev, next);

    printf("[%s] %s -> %s\n", (*dev).name,
           state_name(previous), state_name(next));
    return 0;
}

/*
dev는 원본 구조체를 가리키는 포인터
on/off/toggle로 실제 상태가 바뀔 때만 기록
*/
int cmd_on(Device *dev)
{
    return change_state(dev, DEV_ON);
}

int cmd_off(Device *dev)
{
    return change_state(dev, DEV_OFF);
}

int cmd_toggle(Device *dev)
{
    // ON이면 OFF, OFF면 ON
    return change_state(dev, (*dev).state == DEV_ON ? DEV_OFF : DEV_ON);
}

// 출력만
int cmd_status(Device *dev)
{
    printf("[%s] 현재 상태: %s\n", (*dev).name,
           state_name((*dev).state));
    return 0;
}

// 이름 같은 장치 찾기
Device *find_device(Device *devices[], int count, const char *name)
{
    for (int i = 0; i < count; ++i)
    {
        if (strcmp((*devices[i]).name, name) == 0)
            return devices[i]; // 찾은 장치 주소 반환
    }

    return NULL;
}

/*
hist는 int MAX_LOG개짜리 배열을 가리킴
hist + 1 하면 한 행만큼 이동
0도 OFF 기록이라 빈칸은 log_count로 확인
*/
void print_history(Device *devices[], int device_count, int (*hist)[MAX_LOG])
{
    printf("\n[상태 변화 이력: 오래된 순서 -> 최신 순서]\n");
    printf("%-10s", "device");

    for (int j = 0; j < MAX_LOG; ++j)
        printf("%5d", j + 1);

    putchar('\n');

    for (int i = 0; i < device_count; ++i)
    {
        printf("%-10s", devices[i]->name);

        for (int j = 0; j < MAX_LOG; ++j)
        {
            const char *value = "-";

            // 기록 있는 부분만 출력
            if (j < devices[i]->log_count)
                value = hist[i][j] == DEV_ON ? "on" : "off";

            printf("%5s", value);
        }

        putchar('\n');
    }

    putchar('\n');
}

// 한 줄 입력받기
static int read_line(char line[MAX_INPUT + 2])
{
    if (fgets(line, MAX_INPUT + 2, stdin) == NULL)
        return 0;

    // 입력이 너무 길면 나머지 버림
    if (strlen(line) > MAX_INPUT && strchr(line, '\n') == NULL)
    {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            // 남은 문자 읽어서 버리기
        }

        return -1;
    }

    // 개행 있는 자리를 문자열 끝으로 바꿈
    line[strcspn(line, "\r\n")] = '\0';
    return 1;
}

int main(void)
{
    Device led1 = {"led1", DEV_OFF, {0}, 0};
    Device led2 = {"led2", DEV_OFF, {0}, 0};
    Device sw1 = {"sw1", DEV_OFF, {0}, 0};

    // Device 주소 3개 저장하는 포인터 배열
    Device *devices[DEVICE_COUNT] = {&led1, &led2, &sw1};

    char line[MAX_INPUT + 2];

    for (;;)
    {
        printf("명령 입력:\n");

        int input_result = read_line(line);

        if (input_result == 0)
            break;

        if (input_result == -1)
        {
            printf("오류: 입력은 %d자 이하여야 합니다.\n", MAX_INPUT);
            continue;
        }

        // 입력한 단어 저장
        char name[MAX_INPUT + 1];
        char action[MAX_INPUT + 1];
        char extra[MAX_INPUT + 1];

        // 세 번째 단어는 추가 입력 있는지 확인용
        int word_count = sscanf(line, "%128s %128s %128s",
                                name, action, extra);

        if (word_count < 1)
        {
            printf("오류: 명령을 입력하세요. 예: led1 on\n");
            continue;
        }

        // 종료
        if (strcmp(name, "exit") == 0)
        {
            if (word_count != 1)
            {
                printf("오류: exit는 단독으로 입력하세요.\n");
                continue;
            }

            printf("종료합니다.\n");
            return 0;
        }

        // 전체 장치 기록 보기
        if (strcmp(name, "history") == 0)
        {
            if (word_count != 1)
            {
                printf("오류: history는 단독으로 입력하세요.\n");
                continue;
            }

            // 각 구조체의 log를 실제 2차원 배열로 모음
            int hist[DEVICE_COUNT][MAX_LOG];

            for (int i = 0; i < DEVICE_COUNT; ++i)
                for (int j = 0; j < MAX_LOG; ++j)
                    hist[i][j] = devices[i]->log[j];

            // 배열 포인터 매개변수로 전달
            print_history(devices, DEVICE_COUNT, hist);
            continue;
        }

        // 일반 명령은 장치 이름 + 명령 두 단어
        if (word_count != 2)
        {
            printf("오류: <디바이스이름> <명령어> 형식으로 입력하세요.\n");
            continue;
        }

        Device *dev = find_device(devices, DEVICE_COUNT, name);

        if (dev == NULL)
        {
            printf("오류: 존재하지 않는 디바이스: %s\n", name);
            continue;
        }

        // 실행할 함수 주소 저장
        DevHandler handler = NULL;

        // 배열 전체 크기 / 원소 하나 크기
        size_t command_count = sizeof(command_table) / sizeof(command_table[0]);

        for (size_t i = 0; i < command_count; ++i)
        {
            if (strcmp(action, command_table[i].cmd_name) == 0)
            {
                handler = command_table[i].handler;
                break;
            }
        }

        if (handler == NULL)
        {
            printf("오류: 존재하지 않는 명령어: %s\n", action);
            continue;
        }

        // 함수 포인터로 호출하고 장치 주소 넘김
        int result = handler(dev);

        if (result == -1)
            printf("[%s] 이미 %s 상태입니다 (변경 없음)\n",
                   (*dev).name, state_name((*dev).state));
    }

    // EOF가 아니라 읽기 오류로 끝났는지 확인
    if (ferror(stdin))
    {
        printf("오류: 입력을 읽지 못했습니다.\n");
        return 1;
    }

    return 0;
}