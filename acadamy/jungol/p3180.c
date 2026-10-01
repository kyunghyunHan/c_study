/*
팩토리얼
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 91
long long dp1[MAX];
long long dp2[MAX];
int main(void)
{
    freopen("data.txt", "r", stdin);
    int n;
    scanf("%lld", &n);
    dp1[1] = 1;
    dp2[1] = 0;
    dp1[2] = 0;
    dp2[2] = 1;
    dp1[3] = 1;
    dp2[3] = 1;
    for (int i = 4; i <= n; i++)
    {
        dp1[i] = dp2[i - 1];
        dp2[i] = dp1[i - 1] + dp2[i - 1];
    }
    printf("%lld %lld", dp1[n], dp2[n]);
    return 0;
}