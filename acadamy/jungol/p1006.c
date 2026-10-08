/*
로봇

*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 102
int m, n;

int map[MAX][MAX];
int main(void)
{
    freopen("data.txt", "r", stdin);
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &map[i][j]);
        }
    }

    return 0;
}