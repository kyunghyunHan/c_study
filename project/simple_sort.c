#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
정렬
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
    // 마지막 -1까지
    for (int i = 0; i < len - 1; i++)
    {
        // i+1부터 끝까지
        for (int j = i + 1; j < len; j++)
        {
            // 비교
            // 첫번쨰 배열부터 해서 값을 비교
            // 0보다 크면 스왑
            //오름차순
            //내림차순 하고싶다면 반대
            if (comp(arr + i, arr + j) > 0)
            {
                swap(arr + i, arr + j, size);
            }
        }
    }
}
int main(void)
{
    /* */
    int arr[5][3] = {
        {3, 5, 1},
        {1, 4, 3},
        {7, 1, 5},
        {3, 2, 2},
        {5, 3, 4},
    };
    // c의 qsort
    ssort(arr, 5, sizeof(arr + 0), com);

    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", arr[i][0]);
    }
    return 0;
}