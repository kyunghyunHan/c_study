#include "day09_lib.h"

#include <stdio.h>
int sum_1d(int *a, int r)
{
    int sum = 0;
    for (int i = 0; i < r; i++)
    {
        sum += *(a + i);
    }
    return sum;
}
int sum_2d(int (*a)[4], int r, int c)
{
    int sum = 0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            sum += *(*(a + i) + j);
        }
    }
    return sum;
}
int sum_3d(int (*b)[3][4], int r, int c, int h)
{
    int sum = 0;
    for (int i = 0; i < r; i++)
    {
#if 1
        sum += sum_2d(*(b + i), c, h);
#endif
#if 0
        for (int j = 0; j < c; j++)
        {

            for (int k = 0; k < h; k++)
            {
                sum += *(*(*(b + i) + j) + k);
            }
        }
#endif
    }
    return sum;
}

void exchange0(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void exchange1(int **a, int **b)
{
    int temp = **a;
    **a = **b;
    **b = temp;
}
void exchange2(int ***a, int ***b)
{
    int temp = ***a;
    ***a = ***b;
    ***b = temp;
}

void print_string03(const char *pary[], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        printf("%s\n", pary[i]);
    }
}

void print_1d_array(int *ary, int n)
{
    for (int i = 1; i < n; i++)
    {
        printf("%d ", ary[i]);
    }
    printf("\n");
}
void print_var_array(int **pary, int n)
{
    for (int i = 0; i < n; i++)
    {
        print_1d_array(*(pary + i), **(pary + i));
    }
}
int compint01(const void *a, const void *b)
{
    int ia = *(int *)a;
    int ib = *(int *)b;

    if (ia == ib)
        return 0;
    if (ia > ib)
        return 1;
    return -1;
}

int compint(const void *a, const void *b)
{
    int ia = *(int *)a;
    int ib = *(int *)b;

    return (ia > ib) - (ia < ib);
}


int compint01(const void *a, const void *b)
{
    int ia = *(int *)a;
    int ib = *(int *)b;

    if (ia == ib)
        return 0;
    if (ia > ib)
        return 1;
    return -1;
}

int compint(const void *a, const void *b)
{
    int ia = *(int *)a;
    int ib = *(int *)b;

    return (ia > ib) - (ia < ib);
}
