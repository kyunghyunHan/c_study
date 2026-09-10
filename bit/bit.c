#include "util.h"

int main(void)
{
    int a = 0x33CC33CC;

    printf("%X\n", (1 << 0) | a);
    printf("%X\n", (1 << 5) | a);
    printf("%X\n", (1 << 21) | a);
    printf("%X\n", (1 << 22) | a);
    // 0이 하나라도 있으면 0
    printf("%X\n", a & ~(1 << 0));
    printf("%X\n", a & ~(1 << 5));
    printf("%X\n", a & ~(1 << 21));
    printf("%X\n", a & ~(1 << 22));
    // 두비트가 서로 다르면 1 같으면 0
    printf("%X\n", a ^ (1 << 0));
    printf("%X\n", a ^ (1 << 5));
    printf("%X\n", a ^ (1 << 21));
    printf("%X\n", a ^ (1 << 22));
    return 0;
}