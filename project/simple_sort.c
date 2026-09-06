#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
정렬
*/
void print_arr(int (*arr)[3], size_t rows)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            printf("%d%s", arr[i][j], j == 2 ? "\n" : " ");
        }
    }
}
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
void ssort(void *base, size_t len, size_t size, int (*comp)(const void *, const void *))
{
    char *arr = base;
    // 마지막 -1까지
    for (int i = 0; i < len - 1; i++)
    {
        // i+1부터 끝까지
        for (int j = i + 1; j < len; j++)
        {
            // 비교
            // 첫번쨰 배열부터 해서 값을 비교
            // 0보다 크면 스왑
            // 오름차순
            // 내림차순 하고싶다면 반대
            void *a = arr + i * size;
            void *b = arr + j * size;
            if (comp(a, b) > 0)
            {
                swap(a, b, size);
            }
        }
    }
}
void sssort(int (*arr)[3], size_t rows)
{
    for (size_t i = 0; i < rows; i++)
    {
        ssort(arr[i], 3, sizeof(arr[i][0]), com);
    }

    ssort(arr, rows, sizeof(arr[0]), com);
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
    // ssort(arr, 5, sizeof(arr[0]), com);
    //++
    sssort(arr, 5);
    print_arr(arr, 5);
    return 0;
}