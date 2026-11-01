/*
 * 가상 주변장치 드라이버 - C11 콘솔 프로그램
 * 빌드: gcc -std=c11 -Wall -Wextra device_driver.c -o device_driver
 * 실행: ./device_driver
 *
 * 포인터 개념 5가지의 위치 (아래 [1]~[5] 주석으로 검색 가능)
 * [1] (코드 34행) 함수 포인터: DevHandler, Command, command_table, main의 handler 호출.
 * [2] (코드 118행) 배열 포인터: print_history의 int (*hist)[MAX_LOG].
 * [3] (코드 165행) 포인터 배열: main의 Device *devices[DEVICE_COUNT].
 * [4] (코드 84행) 구조체 포인터: find_device 반환값과 cmd_*의 Device *dev.
 * [5] (코드 76행) 포인터 전달로 원본 수정: change_state의 dev->state 대입.
 *     C는 포인터도 값으로 전달한다. 복사된 주소를 통해 원본을 수정한다.
 *
 * 기본 요구사항의 shift 이력을 사용한다. 초기 상태와 status는 기록하지 않는다.
 * 입력 검증 확장: 128자 초과 및 불필요한 추가 토큰도 거부한다.
 */
#include <stdio.h>
#include <string.h>

#define MAX_LOG 5
#define DEVICE_COUNT 3
#define MAX_INPUT 128

typedef enum { DEV_OFF = 0, DEV_ON = 1 } DevState;

typedef struct Device {
    char name[16];
    DevState state;
    int log[MAX_LOG];
    int log_count;
} Device;

/* [1] Device 주소를 받고 int를 반환하는 함수의 주소를 저장하는 타입. */
typedef int (*DevHandler)(Device *dev);

typedef struct {
    const char *cmd_name;
    DevHandler handler;
} Command;

int cmd_on(Device *dev);
int cmd_off(Device *dev);
int cmd_toggle(Device *dev);
int cmd_status(Device *dev);

static const Command command_table[] = {
    {"on", cmd_on},
    {"off", cmd_off},
    {"toggle", cmd_toggle},
    {"status", cmd_status}
};

static const char *state_name(DevState state)
{
    return state == DEV_ON ? "ON" : "OFF";
}

/* 이력이 가득 차면 가장 오래된 값을 버리고 나머지를 앞으로 옮긴다. */
static void append_log(Device *dev, DevState state)
{
    if (dev->log_count == MAX_LOG) {
        for (int i = 1; i < MAX_LOG; ++i)
            dev->log[i - 1] = dev->log[i];
        --dev->log_count;
    }
    dev->log[dev->log_count++] = (int)state;
}

static int change_state(Device *dev, DevState next)
{
    if (dev->state == next)
        return -1; /* 같은 상태: 대입, 기록, 성공 출력 모두 생략한다. */

    DevState previous = dev->state;
    /* [5] 포인터로 전달받은 주소의 원본 Device를 직접 수정한다. */
    dev->state = next;
    append_log(dev, next);
    printf("[%s] %s -> %s\n", dev->name,
           state_name(previous), state_name(next));
    return 0;
}

/* [4] dev는 Device 복사본이 아니라 원본 구조체를 가리키는 포인터다. */
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
    return change_state(dev, dev->state == DEV_ON ? DEV_OFF : DEV_ON);
}

int cmd_status(Device *dev)
{
    printf("[%s] 현재 상태: %s\n", dev->name, state_name(dev->state));
    return 0; /* 조회는 이력을 추가하지 않는다. */
}

Device *find_device(Device *devices[], int count, const char *name)
{
    for (int i = 0; i < count; ++i) {
        if (strcmp(devices[i]->name, name) == 0)
            return devices[i];
    }
    return NULL;
}

/* [2] hist는 MAX_LOG개의 int로 이루어진 한 행을 가리킨다.
 * hist + 1은 int 한 개가 아니라 행 하나(MAX_LOG개)만큼 이동한다.
 * 값 0은 유효한 OFF 기록이므로 빈 칸 여부는 log_count로 판단한다.
 */
void print_history(Device *devices[], int device_count, int (*hist)[MAX_LOG])
{
    printf("\n[상태 변화 이력: 오래된 순서 -> 최신 순서]\n");
    printf("%-10s", "device");
    for (int j = 0; j < MAX_LOG; ++j)
        printf("%5d", j + 1);
    putchar('\n');

    for (int i = 0; i < device_count; ++i) {
        printf("%-10s", devices[i]->name);
        for (int j = 0; j < MAX_LOG; ++j) {
            const char *value = "-";
            if (j < devices[i]->log_count)
                value = hist[i][j] == DEV_ON ? "on" : "off";
            printf("%5s", value);
        }
        putchar('\n');
    }
    putchar('\n');
}

/* 반환: 1=정상 입력, -1=길이 초과, 0=EOF 또는 읽기 오류.
 * 128글자 + 개행 + 널 문자를 담을 수 있게 버퍼를 확보한다.
 * 긴 줄은 남은 부분까지 소비하여 다음 명령과 섞이지 않게 한다.
 */
static int read_line(char line[MAX_INPUT + 2])
{
    if (fgets(line, MAX_INPUT + 2, stdin) == NULL)
        return 0;

    if (strlen(line) > MAX_INPUT && strchr(line, '\n') == NULL) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* 초과한 줄의 나머지를 버린다. */
        }
        return -1;
    }
    line[strcspn(line, "\r\n")] = '\0';
    return 1;
}

int main(void)
{
    Device led1 = {"led1", DEV_OFF, {0}, 0};
    Device led2 = {"led2", DEV_OFF, {0}, 0};
    Device sw1  = {"sw1",  DEV_OFF, {0}, 0};
    /* [3] 원소가 Device가 아닌 Device *인 포인터 배열. */
    Device *devices[DEVICE_COUNT] = {&led1, &led2, &sw1};
    char line[MAX_INPUT + 2];
    const char *separators = " \t\r\n\v\f";

    for (;;) {
        printf("> ");
        fflush(stdout); /* 개행 없는 프롬프트도 즉시 보이게 한다. */
        int input_result = read_line(line);
        if (input_result == 0)
            break;
        if (input_result == -1) {
            printf("오류: 입력은 %d자 이하여야 합니다.\n", MAX_INPUT);
            continue;
        }

        /* strtok은 line을 분리하며, 각 토큰은 line 내부를 가리킨다. */
        char *name = strtok(line, separators);
        char *action = strtok(NULL, separators);
        char *extra = strtok(NULL, separators);
        if (name == NULL) {
            printf("오류: 명령을 입력하세요. 예: led1 on\n");
            continue;
        }

        if (strcmp(name, "exit") == 0) {
            if (action != NULL) {
                printf("오류: exit는 단독으로 입력하세요.\n");
                continue;
            }
            printf("종료합니다.\n");
            return 0;
        }

        if (strcmp(name, "history") == 0) {
            if (action != NULL) {
                printf("오류: history는 단독으로 입력하세요.\n");
                continue;
            }
            /* 구조체 멤버 log들은 연속된 2차원 배열이 아니다.
             * 강제 형변환하지 않고 실제 2차원 배열에 모아서 전달한다.
             */
            int hist[DEVICE_COUNT][MAX_LOG];
            for (int i = 0; i < DEVICE_COUNT; ++i)
                for (int j = 0; j < MAX_LOG; ++j)
                    hist[i][j] = devices[i]->log[j];
            print_history(devices, DEVICE_COUNT, hist);
            continue;
        }

        if (action == NULL || extra != NULL) {
            printf("오류: <디바이스이름> <명령어> 형식으로 입력하세요.\n");
            continue;
        }

        Device *dev = find_device(devices, DEVICE_COUNT, name);
        if (dev == NULL) {
            printf("오류: 존재하지 않는 디바이스: %s\n", name);
            continue;
        }

        DevHandler handler = NULL;
        size_t command_count = sizeof(command_table) / sizeof(command_table[0]);
        /* 네 동작의 선택은 if-else/switch 분기가 아닌 테이블 탐색이다. */
        for (size_t i = 0; i < command_count; ++i) {
            if (strcmp(action, command_table[i].cmd_name) == 0) {
                handler = command_table[i].handler;
                break;
            }
        }
        if (handler == NULL) {
            printf("오류: 존재하지 않는 명령어: %s\n", action);
            continue;
        }

        /* [1] 함수 포인터 호출. 성공 출력은 핸들러의 책임이다. */
        int result = handler(dev);
        if (result == -1)
            printf("[%s] 이미 %s 상태입니다 (변경 없음)\n",
                   dev->name, state_name(dev->state));
    }
    if (ferror(stdin)) {
        fprintf(stderr, "오류: 입력을 읽지 못했습니다.\n");
        return 1;
    }
    return 0;
}
