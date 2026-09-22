#include <stdio.h>
#include <stdlib.h>
#define MAX 100000
/*qsort의 활용 */
int compare(const void *left, const void *right)
{
    int a = *(const int *)left;
    int b = *(const int *)right;

    return (a > b) - (a < b);
}

int main(void)
{
    int n;
    int arr[MAX];

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int s, e;
    scanf("%d %d", &s, &e);

    qsort(arr + s,
          (size_t)(e - s + 1),
          sizeof(arr[0]),
          compare);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    qsort(arr, (size_t)n, sizeof(arr[0]), compare);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
