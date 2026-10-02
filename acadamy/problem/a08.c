/*
2차원 누적합

H  W칸
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 1501
int arr[MAX][MAX];
int map[MAX][MAX];
int main(void)
{
    freopen("data.txt", "r", stdin);
    int h, w;
    scanf("%d %d", &h, &w);
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            scanf("%d", &arr[i][j]);
            map[i][j] = arr[i][j] + map[i][j - 1];
        }
    }
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            map[i][j] = map[i - 1][j] + map[i][j];
        }
    }
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int x, y, k, l;
        scanf("%d %d %d %d", &x, &y, &k, &l);
        printf("%d\n",
               map[k][l] - map[x - 1][l] - map[k][y - 1] + map[x - 1][y - 1]);
    }
    return 0;
}