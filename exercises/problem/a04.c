#include <stdio.h>

int main()
{
    int n = 13;

    for (int x = 9; x >= 0; x--)
    {
        int wari = (1 << x);
        printf("%d", (n / wari) % 2);
    }
    return 0;
}