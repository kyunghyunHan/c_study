/*
배열의 바이너리 서치
15 47
11 13 17 19 23 29 31 37 41 43 47 53 59 61 67
*/
#include <stdio.h>
#include <stdlib.h>
int arr[1000001];
int binary_search(int target, int len)
{
    int left = 0;
    int right = len - 1;
    while (left <= right)
    {
        int mid = (right + left) / 2;
        if (target == arr[mid])
        {
            return mid;
        }
        if (target > arr[mid])
        {
            left = mid + 1;
        }
        if (target < arr[mid])
        {
            right = mid - 1;
        }
    }
}
int main(void)
{
    freopen("data.txt", "r", stdin);
    int n, x;
    scanf("%d %d", &n, &x);
    int len = n;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int result = binary_search(x, len);
    printf("%d\n", result);

    return 0;
}