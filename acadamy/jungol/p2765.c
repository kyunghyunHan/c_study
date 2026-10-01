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
int used2[MAX][MAX];

int n;
void dfs(int start_y, int start_x, char c)
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
        if (arr[next_y][next_x] == c)
        {
            dfs(next_y, next_x, arr[next_y][next_x]);
        }
    }
}

void dfs2(int start_y, int start_x, char c)
{
    used2[start_y][start_x] = 1;

    for (int i = 0; i < 4; i++)
    {
        int next_x = start_x + dx[i];
        int next_y = start_y + dy[i];

        if (used2[next_y][next_x] == 1)
        {
            continue;
        }
        if (c == 'R' || c == 'G')
        {
            if (arr[next_y][next_x] == 'R' ||
                arr[next_y][next_x] == 'G')
            {
                dfs2(next_y, next_x, arr[next_y][next_x]);
            }
        }
        else
        {
            if (arr[next_y][next_x] == 'B')
            {
                dfs2(next_y, next_x, 'B');
            }
        }
    }
}
int main(void)
{
    int cnt = 0;
    int cnt2 = 0;
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
                dfs(i, j, arr[i][j]);
                cnt++;
            }
            if (used2[i][j] == 0)
            {
                dfs2(i, j, arr[i][j]);
                cnt2++;
            }
        }
    }
    printf("%d %d", cnt, cnt2);
    return 0;
}
