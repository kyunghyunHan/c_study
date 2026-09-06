#include <stdio.h>
/*


*/
int com(const void *a, const void *b)
{
    int ca = *(int *)a;
}

void ssort(int *arr, size_t len, size_t size, int (*comp)(const void *, const void *));
int main(void)
{
    int arr[5][3] = {
        {3, 5, 1},
        {1, 4, 3},
        {7, 1, 5},
        {3, 2, 2},
        {5, 3, 4},
    };
    // ssort();
    return 0;
}