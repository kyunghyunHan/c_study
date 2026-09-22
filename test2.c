#include <stdio.h>
#include <stdlib.h>
#define MAX (500000)
int n;
int arr[MAX];
int q;
int brr[MAX];
int target = 2;
int binary_search(int right, int left)
{

    int mid = (left + right) / 2;
    if (target == arr[mid])
    {

        return mid;
    }
    else if (target > arr[mid])
    {
        left = mid + 1;
        binary_search(left, right);
    }
    else
    {
        right = mid - 1;
        binary_search(left, right);
    }
    return -1;
}
int binary_search(int arr[], int size, int target)
{
    int mid;
    int right = size - 1;
    int left = 0;

    while (left <= right)
    {
        mid = (left + right) / 2;
        if (target == arr[mid])
        {
            return mid;
        }
        else if (target > arr[mid])
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}
int main(void)
{
    int arr[7] = {1, 2, 3, 4, 8, 9, 10};
    printf("%d ", binary_search(0, 7 - 1));

    return 0;
}