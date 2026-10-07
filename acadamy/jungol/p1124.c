/*
색종이(고)
누적합??

*/
#include <stdio.h>
#include <stdlib.h>
int arr[102][102] = {0};
int main(void)
{
    freopen("data.txt", "r", stdin);
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        for (int i = y; i <= y + 10; i++)
        {
            for (int j = x; j <= x + 10; j++)
            {
                if (arr[i][j] == 0)
                {
                    arr[i][j] = 1;
                }
                if (arr[i][j - 1] >= 1)
                {
                    arr[i][j] = arr[i][j - 1] + 1;
                }
            }
        }
    }
    for (int i = 1; i < 101; i++)
    {
        for (int j = 1; j < 101; j++)
        {
            if (arr[i][j] != 0)
            {
                arr[i][j] += arr[i - 1][j];
            }
        }
    }
    int max = 0;
    for (int i = 1; i < 101; i++)
    {
        for (int j = 1; j < 101; j++)
        {
            if (max < arr[i][j])
            {
                max = arr[i][j];
            }
            printf("%d", arr[i][j]);
        }
        printf("\n");
    }
    printf("%d", max);

    return 0;
}