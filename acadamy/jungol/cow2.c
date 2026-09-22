#include <stdio.h>
#include <stdlib.h>

int com(const void *a, const void *b)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

/*
 int binary_search_max(int *arr , int s , int e ,int max){
 int m  = -1;
 int res =-1;
}

*/
int main(void)
{
    int n;

    long long cnt = 0;
    if (scanf("%d", &n) != 1)
    {
        return 1;
    }

    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    // 소를 왼쪽에서 오른쪽 순서로 정렬한다.
    // 정렬 후 i < j < k이면 위치도 arr[i] < arr[j] < arr[k]이다.
    qsort(arr, n, sizeof(int), com);

    // i: 공을 처음 던지는 소 X
    for (int i = 0; i < n - 2; ++i)
    {
        /*
         * lower: 세 번째 소 Z가 될 수 있는 첫 번째 인덱스
         * upper: 세 번째 소 Z가 될 수 없는 첫 번째 인덱스
         *
         * 가능한 Z의 범위는 [lower, upper)이므로
         * 가능한 소의 수는 upper - lower이다.
         */
        int lower = i + 2;
        int upper = i + 2;

        // j: 두 번째로 공을 받는 소 Y
        for (int j = i + 1; j < n - 1; ++j)
        {
            // 첫 번째 공의 이동 거리: X -> Y
            long long d1 = (long long)arr[j] - arr[i];

            /*
             * 두 번째 거리(Y -> Z)는 d1 이상, 2*d1 이하여야 한다.
             * 따라서 세 번째 소 Z의 위치 범위는 다음과 같다.
             *
             * arr[j] + d1 <= Z의 위치 <= arr[j] + 2*d1
             */
            long long min_position = (long long)arr[j] + d1;
            long long max_position = (long long)arr[j] + d1 * 2;

            // 세 번째 소는 반드시 j보다 오른쪽에 있어야 한다.
            if (lower < j + 1)
            {
                lower = j + 1;
            }

            // min_position 이상인 값이 처음 나오는 위치를 찾는다.
            while (lower < n && arr[lower] < min_position)
            {
                ++lower;
            }

            // upper는 lower보다 왼쪽에 있을 수 없다.
            if (upper < lower)
            {
                upper = lower;
            }

            // max_position보다 큰 값이 처음 나오는 위치를 찾는다.
            while (upper < n && arr[upper] <= max_position)
            {
                ++upper;
            }

            /*
             * j가 오른쪽으로 이동하면 min_position과 max_position도
             * 커지므로 lower와 upper를 처음부터 다시 찾을 필요가 없다.
             * 이전 위치에서 계속 오른쪽으로 이동하면 된다.
             */
            cnt += upper - lower;
        }
    }
    printf("%lld\n", cnt);

    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d", arr[i]);
    // }
    return 0;
}
