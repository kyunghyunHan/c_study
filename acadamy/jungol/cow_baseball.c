#include <stdio.h>
#include <stdlib.h>

int com(const void *a, const void *b)
{
    int ia = *(int *)a;
    int ib = *(int *)b;
    return (ia > ib) - (ia < ib);
}

long long binary_search(const int arr[], int left, int right, int target, int upper)
{
    while (left < right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] > target || (!upper && arr[mid] == target))
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    return left;
}

int main(void)
{
    int n;
    long long cnt = 0;
    // freopen("jungol.txt", "r", stdin);
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    qsort(arr, n, sizeof(int), com);

    for (int i = 0; i < n - 2; ++i)
    {
        for (int j = i + 1; j < n - 1; ++j)
        {
            int d1 = arr[j] - arr[i];
            long long min_position = arr[j] + d1;
            long long max_position = arr[j] + d1 * 2;

            long long first = binary_search(arr, j + 1, n, min_position, 0);
            long long last = binary_search(arr, j + 1, n, max_position, 1);

            cnt += last - first;
        }
    }

    printf("%d", cnt);
    return 0;

#if 0
    for (int i = 0; i < n - 2; ++i)
    {
        for (int j = i + 1; j < n - 1; ++j)
        {
            int d1 = arr[j] - arr[i];
            binary_search()
            // for (int k = j + 1; k < n; ++k)
            // {
            //     int d2 = arr[k] - arr[j];

            //     if (d2 < d1)
            //     {
            //         continue;
            //     }

            //     if (d2 > d1 * 2)
            //     {
            //         break;
            //     }
            //     cnt++;
            // }
        }
    }
    printf("%d", cnt);
#endif

    return 0;
}
