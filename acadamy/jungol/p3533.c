#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int dp[100000];
    int n = 182;
    dp[1] = 1;
    dp[2] = 1;
    for (int i = 3; i <= n; i++)
    {
        dp[i] = (dp[i - 2] + dp[i - 1]) % 100000007;
    }
    printf("%d", dp[n]);
    return 0;
}