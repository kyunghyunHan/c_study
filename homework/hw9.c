/*
과제

가사 제어보드 디바이스 3개
LED 1 , LED 2, SWITCH1

명령어 led1 on , sw1 toggle , led2

*/

#define MAX_LOG 5

typedef enum
{
    DEF_OFF = 0,
    DEV_ON = 1
} DevState;

typedef struct Device
{
    char name[16];
    DevState state;
    int log[MAX_LOG]; // 상태가
    int log_count;
} Device;

typedef int (*DevHandler)(Device *dev);
typedef struct
{
    const char *cmd_name;
    DevHandler handler;

} Command;