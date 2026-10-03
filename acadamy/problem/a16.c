/*
dungeon 1


던전에 1부터 n 까지의 번호가 붙어있는 N개의 방

5
2 4 1 3
5 3 7

*/
#include "problem.h"
int a[100];
int b[100];
int dp[100000];
#define min(x, y) ((x) < (y) ? (x) : (y))

int main(void)
{
    freopen("data.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    dp[1] = 0;
    dp[2] = a[1];
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n - 2; i++)
    {
        scanf("%d", &b[i]);
    }
    for (int i = 3; i <= n; i++)
    {
        dp[i] = (int)min(
            dp[i - 1] + a[i - 1], dp[i - 2] + b[i - 2]);
    }
    printf("%d", dp[n]);
    return 0;
}