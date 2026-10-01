/*
계단 오르기 11

4

1 1 1 1
1 2 1
1 1 2
2 1 1
2 2


1 1 1 1 1
1 1 1 2
1 1 2 1
1 2 1 1
2 1 1 1
2 2 1
2 1 2
1 2 2
2
dp 1 = 1
dp 2=  3
dp 3 = 4
dp 4 = 5
dp 5 = 8

*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 16
int dp[MAX];
int main(void)
{
    freopen("data.txt", "r", stdin);
    int n;
    scanf("%d", &n);

    dp[1] = 1;
    dp[2] = 3;
    dp[3] = 4;
    for (int i = 4; i < MAX; i++)
    {
        dp[i] = (dp[i - 1] + dp[i - 2]);
    }

    printf("%d", dp[n]);
    return 0;
}