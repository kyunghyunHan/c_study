/*
dungeon 1


던전에 1부터 n 까지의 번호가 붙어있는 N개의 방

5
2 4 1 3
5 3 7

*/
#include "problem.h"
int a[100009];
int b[100009];
int dp[100009];
#define min(x, y) ((x) < (y) ? (x) : (y))

int main(void)
{
    freopen("data.txt", "r", stdin);
    int n;
    scanf("%d", &n);

    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 3; i <= n; i++)
    {
        scanf("%d", &b[i]);
    }
    dp[1] = 0;
    dp[2] = a[2];
    for (int i = 3; i <= n; i++)
    {
        dp[i] = (int)min(
            dp[i - 1] + a[i], dp[i - 2] + b[i]);
    }
    printf("%d", dp[n]);
    return 0;
}