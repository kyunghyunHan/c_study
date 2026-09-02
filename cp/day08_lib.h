#ifndef DAY08_LIB_H
#define DAY08_LIB_H

#include <stddef.h>

#define SIZE(a) (sizeof(a) / sizeof((a)[0]))

void input1Darray(int row, int col, int *array);
void input2Darray(int row, int col, int (*array)[col]);
void print2Darray(int row, int col, int *array);
#endif
