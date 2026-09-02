#include <stdio.h>

#if 1
#define SIZE(a) (sizeof(a) / sizeof((a)[0]))

void intput2Darray(int (*score)[4], int row, int col)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", &score[i][j]);
        }
    }
}
void print2Darray(int row, int col, int array[row][col])
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            scanf("%d", &array[i][j]);
        }
    }
}
int main(void)
{
    int score[3][4] = {0};

    intput2Darray(score, SIZE(score), SIZE(score[0]));

    return 0;
}

#endif
