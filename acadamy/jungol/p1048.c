#include <stdio.h>

long long dp[21];

int main(void)
{
    int n;
    scanf("%d", &n);

    dp[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        dp[i] = i * dp[i - 1];
    }

    int cnt = 0;

    while (dp[n] > 0 && dp[n] % 10 == 0)
    {
        cnt++;
        dp[n] /= 10;
    }

    printf("%d", cnt);
    return 0;
}