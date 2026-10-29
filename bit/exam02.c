#include <stdio.h>
#include <stdint.h>

int main(void)
{

    uint32_t IDR = 0x00000028;

    00101000;
    uint32_t mask = (1U << 3) | (1U << 5);
    // 3번 5번비트가 모두1이면
    if ((IDR && mask) == mask)
    {
    }
    // 하나라도 1이라면
    if ((IDR & mask) != 0)
    {
    }
    int out = 0xff;
    int p = (0x5U << 5) | (out & ~(0x7U << 5));
    return 0;
}