/*
1차원 누적합2

D일에 걸쳐 이벤트
N 명이 출석
*/
#include <stdio.h>
#include <stdlib.h>
#if 0
int arr[100001];
int main(void)
{
    freopen("data.txt", "r", stdin);
    int d, n;
    scanf("%d", &d);
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d %d\n", l, r);

        for (int j = l; j <= r; j++)
        {
            arr[j]++;
        }
    }
    for (int i = 1; i <= d; i++)
    {
        printf("%d\n", arr[i]);
    }
    return 0;
}
#endif

int n, l[100009], r[100009];
int d, b[100009];
int answer[100009];

int main(void)
{

    freopen("data.txt", "r", stdin);
    scanf("%d %d", &d, &n);

    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d", &l[i], &r[i]);
    }

    for (int i = 1; i <= n; i++)
    {
        b[l[i]] += 1;
        b[r[i] + 1] -= 1;
    }

    answer[0] = 0;

    for (int k = 1; k <= d; k++)
    {
        answer[k] = answer[k - 1] + b[k];
    }
    for (int k = 1; k <= d; k++)
    {
        printf("%d", answer[k]);
    }
    return 0;
}