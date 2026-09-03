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
int sum_2d(int(*a)[4], int r, int c)
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
int sum_3d(int (*b)[3][4],int r , int c, int h){
    int sum = 0;
    int b1 = 0;
    for (int i = 0; i<r;i++){
        #if !b1
        sum += sum_2d(*(b+i),c,h);
        #endif
        #if b1
        for (int j = 0; j<c;j++){

            for (int k = 0; k<h;k++){
                sum+=*(*(*(b+i)+j)+k);
            }
        }
        #endif
    }
    return sum;
}