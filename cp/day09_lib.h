#ifndef DAY09_LIB_H
#define DAY09_LIB_H

#define SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define STRING_LENGTH 10

#include <stddef.h>
#include <stdio.h>
int sum_2d(int (*a)[4], int r, int c);
int sum_1d(int *a, int r);
int sum_3d(int (*b)[3][4], int r, int c, int h);
void exchange0(int *a, int *b);
void exchange1(int **a, int **b);
void exchange2(int ***a, int ***b);
void print_string03(const char *pary[], size_t count);
void print_1d_array(int *ary, int n);
void print_var_array(int **pary, int n);

#endif
