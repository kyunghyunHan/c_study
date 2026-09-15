#ifndef DAY08_LIB_H
#define DAY08_LIB_H

#define SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define STRING_LENGTH 10

void input1Darray(int row, int col, int *array);
void input2Darray(int row, int col, int (*array)[col]);
void print2Darray(int row, int col, int *array);

void input_strings(char (*animal)[STRING_LENGTH], int n);
void print_strings(const char (*animal)[STRING_LENGTH], int n);
void print_strings02(const char **animal, int n);

#endif
