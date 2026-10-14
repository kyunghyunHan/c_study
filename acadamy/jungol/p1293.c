#include <stdio.h>

int dp[31];

int main(void)
{
    int n;
    scanf("%d", &n);

    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + 2 * dp[i - 2];
    }

    // 뒤집어도 자기 자신과 같은 배치 수
    int sym;

    if (n % 2 == 1)
    {
        sym = dp[n / 2];
    }
    else
    {
        sym = dp[n / 2] + 2 * dp[n / 2 - 1];
    }

    // 대칭이 아닌 배치는 두 개를 하나로 합치고,
    // 대칭인 배치는 그대로 유지
    int answer = (dp[n] - sym) / 2 + sym;

    printf("%d\n", answer);
    return 0;
}