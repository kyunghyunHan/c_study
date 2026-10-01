/*
미술관람 대회

N * N픽셀

구현


*/
int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, -1, 1};
#include <stdio.h>
#include <stdlib.h>
#define MAX 102
char arr[MAX][MAX];
int used[MAX][MAX];
int n;
void dfs(int start_y, int start_x)
{
    used[start_y][start_x] = 1;

    for (int i = 0; i < 4; i++)
    {
        int next_x = start_x + dx[i];
        int next_y = start_y + dy[i];

        if (used[next_y][next_x] == 1)
        {
            continue;
        }

    }
}
int main(void)
{
    freopen("data.txt", "r", stdin);
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf(" %c", &arr[i][j]);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (used[i][j] == 0)
            {
                dfs(i, j);
                
            }
        }
    }

    return 0;
}
