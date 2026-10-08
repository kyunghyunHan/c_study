/*
내리막길

*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 502
int map[MAX][MAX];
int dp[MAX][MAX];
int m, n;

int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};

int cnt = 0;
int dfs(int start_y, int start_x)
{
    if (start_y == m && start_x == n)
    {

        return 1;
    }

    if (dp[start_y][start_x] != -1)
    {
        return dp[start_y][start_x];
    }

    dp[start_y][start_x] = 0;

    for (int i = 0; i < 4; i++)
    {
        int next_y = start_y + dy[i];
        int next_x = start_x + dx[i];
        if (next_y < 1 || next_y > m || next_x < 1 || next_x > n)
        {
            continue;
        }
        if (map[next_y][next_x] >= map[start_y][start_x])
        {
            continue;
        }
        dp[start_y][start_x] += dfs(next_y, next_x);
    }
    return dp[start_y][start_x];
}
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
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dp[i][j] = -1;
        }
    }
    printf("%d\n", dfs(1, 1));

    return 0;
}