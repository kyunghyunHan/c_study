/*
강아지와 병아리
*/
#include <stdio.h>

int main(void)
{
    while (1)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a == 0 && b == 0)
        {
            break;
        }
        if (a + b > 4000)
        {
            printf("INPUT ERROR!");
        }
    }
    return 0;
}