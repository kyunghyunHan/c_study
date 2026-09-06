#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*


*/
int com(const void *a, const void *b)
{
    int ca = *(int *)a;
    int cb = *(int *)b;

    if (ca > cb)
        return 1;
    if (ca < cb)
        return -1;
    return 0;
}
void swap(void *a, void *b, int size)
{
    char *temp = NULL;
    temp = malloc(size);
    if (temp == NULL)
    {
        return;
    }
    memmove(temp, a, size);
    memmove(a, b, size);
    memmove(b, temp, size);
    free(temp);
}
void ssort(int *arr, size_t len, size_t size, int (*comp)(const void *, const void *))
{

    for (int i = 0; i < len - 1; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (comp(arr + i, arr + j) > 0)
            {
                swap(arr + i, arr + j, size);
            }
        }
    }
}
int main(void)
{
    int arr[5][3] = {
        {3, 5, 1},
        {1, 4, 3},
        {7, 1, 5},
        {3, 2, 2},
        {5, 3, 4},
    };
    ssort(arr, 5, sizeof(arr + 0), com);

    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", arr[i][0]);
    }
    return 0;
}