#include "day08_lib.h"

#include <stdio.h>

void input1Darray(int row, int col, int *array)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", array + i * col + j);
        }
    }
}

void input2Darray(int row, int col, int (*array)[col])
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", *(array + i) + j);
        }
    }
}

void print2Darray(int row, int col, int *array)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%3d ", *(array + i * col + j));
        }
        printf("\n");
    }
}

void input_strings(char (*animal)[STRING_LENGTH], int n)
{
    for (int i = 0; i < n; i++) {
        (void)scanf("%9s", animal[i]);
    }
}

void print_strings(const char (*animal)[STRING_LENGTH], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%s\n", animal[i]);
    }
}

void print_strings02(const char **animal, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%s\n", animal[i]);
    }
}
