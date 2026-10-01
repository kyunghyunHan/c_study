/* 게단 오르기*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 31
int dp[MAX];
int main(void)
{
    freopen("data.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;
    dp[4] = 5;

    for (int i = 5; i <= MAX; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    printf("%d", dp[n]);
    return 0;
}