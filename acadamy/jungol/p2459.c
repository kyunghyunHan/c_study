/*
지능형 기차

*/

#include <stdio.h>
int main(void)
{
    int cnt = 0;
    int max = 0;

    freopen("data.txt", "r", stdin);
    for (int i = 0; i < 4; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        cnt += b;
        cnt -= a;
        if (max < cnt)
        {
            max = cnt;
        }
    }
    printf("%d", max);
    return 0;
}
