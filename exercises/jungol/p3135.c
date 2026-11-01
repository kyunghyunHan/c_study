
/*
const 구간의 합구하기
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000001
int main(void)
{   
    freopen("jungol.txt", "r", stdin);
    //초기값
    long long arr[MAX] = {0};
    long long n;
    scanf("%lld", &n);

    for (long long i = 1; i <= n; i++)
    {
        long long temp;
        scanf("%lld", &temp);
        arr[i] += (temp + arr[i - 1]);
    }
    long long q;
    scanf("%lld", &q);
    for (long long i = 1; i <= q; i++)
    {
        long long x, y, sum;
        sum = 0;
        scanf("%lld %lld", &x, &y);
        // prlong longf("%d %d\n", arr[y], arr[x]);

        sum = arr[y] - arr[x - 1];
        // for (long long i = x; i <= y; i++)
        // {
        //     sum += arr[i];
        // }
        printf("%lld\n", sum);
    }

    return 0;
}