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

        for (int i = y; i < y + 10; i++)
        {
            for (int j = x; j < x + 10; j++)
            {
                arr[i][j] = 1;
            }
        }
    }
    for (int i = 0; i < 100; i++)
    {
        for (int j = 1; j < 100; j++)
        {
            if (arr[i][j] != 0)
            {
                arr[i][j] = arr[i][j - 1] + 1;
            }
        }
    }
    int max = 0;

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            int width = arr[i][j];

            for (int k = i; k >= 0; k--)
            {

                if (width > arr[k][j])
                {
                    width = arr[k][j];
                }

                int area = width * (i - k + 1);

                if (max < area)
                {
                    max = area;
                }
            }
        }
    }
    printf("%d", max);

    return 0;
}