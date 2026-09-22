/*

두줄로 타일깔기
세로의 칸수 100000
20100529로 나눈값 출력

입력 6 출력 43

*/

#include <stdio.h>
#include <stdlib.h>
#define MAX (1000000)
int dp[MAX];
int main(void)
{
    int n;
    scanf("%d", &n);
    dp[1] = 0;
    dp[2] = 3;
    dp[3] = 5;
    for (int i = 4; i <= n; i++)
    {
        dp[i] = (dp[i - 2] * 2 + dp[i - 1]) % 20100529;
    }

    printf("%d", dp[n]);
    return 0;
}