/*
위성사진

*/
#include <stdio.h>
#include <stdlib.h>
#define WMAX 82
#define HMAX 1002
int map[HMAX][WMAX];
int used[HMAX][WMAX];
int w, h;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
int result = 0;
int cnt;
void dfs(int start_y, int start_x)
{
    used[start_y][start_x] = 1;
    cnt++;

    for (int i = 0; i < 4; i++)
    {
        int next_y = start_y + dy[i];
        int next_x = start_x + dx[i];

        if (next_x < 1 || next_x > w || next_y < 1 || next_y > h)
        {
            continue;
        }

        if (used[next_y][next_x] == 1 || map[next_y][next_x] == 0)
        {
            continue;
        }
        dfs(next_y, next_x);
    }
}
int main(void)
{

    preopen("data.txt", "r", stdin);
    scanf("%d %d", &w, &h);
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            char c;
            scanf(" %c", &c);
            if (c == '*')
                map[i][j] = 1;
            else
                map[i][j] = 0;
        }
    }

    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            if (map[i][j] == 1 && used[i][j] == 0)
            {
                cnt = 0;
                dfs(i, j);
                if (cnt > result)
                    result = cnt;
            }
        }
    }
    printf("%d", result);
    return 0;
}