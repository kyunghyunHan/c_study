/*
가로등 위치는 왼쪽부터 a1 a2 a3..
위치 x의 어두운 정도를 그 위치로부터 가장 가까운 가로등 까지의 거리로 정의
 L 총거리
 N  배열의 개수
 K  개의 가로등
 arr

 0 1 2 3 4 5 6 7 8 9 10
 1 * 1 1 * 1 1 1 * 1

 current는 while 안에
 범위체크
 used활요
 범위검사는 무조건 먼저

 //아직 못품
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 5000001
long long arr[MAX];
long long queue[MAX];
long long used[MAX];
long long rear, front;
long long dx[2] = {-1, 1};

int com(const void *a, const void *b)
{
    long long ia = *(const long long *)a;
    long long ib = *(const long long *)b;
    return (ia > ib) - (ia < ib);
}
int main(void)
{
    long long l, n, k;

    freopen("jungol.txt", "r", stdin);
    if (scanf("%lld %lld %lld", &l, &n, &k) != 3 ||
        l < 0 || l >= MAX || n < 0 || n > MAX ||
        k < 0 || k > l + 1)
    {
        return 1;
    }

    for (long long i = 0; i <= l; i++)
    {
        arr[i] = -1;
    }
    for (long long i = 0; i < n; i++)
    {
        long long temp;
        scanf("%lld", &temp);
        arr[temp] = 0;
        used[temp] = 1;
        queue[rear++] = temp;
    }
    while (front < rear)
    {
        long long current = queue[front++];

        for (long long i = 0; i < 2; i++)
        {
            long long next_x = current + dx[i];
            if (next_x < 0 || next_x > l)
            {
                continue;
            }
            if (used[next_x] == 1)
            {
                continue;
            }

            arr[next_x] = arr[current] + 1;
            queue[rear++] = next_x;
            used[next_x] = 1;
        }
    }

    qsort(arr, l + 1, sizeof(long long), com);

    for (long long i = 0; i < k; i++)
    {
        printf("%lld\n", arr[i]);
    }

    return 0;
}
