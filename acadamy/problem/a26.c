/*
소수판정

2로 나누어 떨어지지 않고 3으로 떨어지지 않고 4로 나누어 떨어지지않은면
2부터
 */
#include <stdio.h>
#include <stdlib.h>
int q, x[10009], n=30000;
int deleted[300009];
int is_prime(int x)
{
    for (int i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    freopen("data.txt", "r", stdin);
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        scanf("%d", &x[i]);
    }
    for (int i = 2; i <= n; i++)
    {
        deleted[i] = 0;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (deleted[i] == 1)
        {
            continue;
        }
        for (int j = i * 2; j <= n; j += i)
        {
            deleted[j] = 1;
        }
    }

    for (int i = 1; i <= q; i++)
    {
        if (deleted[x[i]] == 0)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
    return 0;
}