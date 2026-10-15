/*목장 수호*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 702
typedef struct Point
{
    int y, x;
} Point;
int n, m;
Point queue[MAX * MAX];
int front, rear;
int map[MAX][MAX];
int used[MAX][MAX];
int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
int dx[8] = {0, 0, 1, -1, -1, -1, 1, 1};
int bfs(int start_y, int start_x)
{
    int is_peak = 1;

    used[start_y][start_x] = 1;
    queue[rear++] = (Point){start_y, start_x};

    while (front < rear)
    {
        Point current = queue[front++];

        for (int i = 0; i < 8; i++)
        {
            int next_y = current.y + dy[i];
            int next_x = current.x + dx[i];
            // 범위를 벗어나면안댐
            if (next_y < 1 || next_y > n || next_x < 1 || next_x > m)
            {
                continue;
            }
            if (map[next_y][next_x] > map[current.y][current.x])
            {
                is_peak = 0;
            }
            // 방문한곳이 아니여야함
            if (used[next_y][next_x] == 1)
            {
                continue;
            }
            // 다음곳이 현재곳보다 크면
            if (map[next_y][next_x] != map[current.y][current.x])
            {
                continue;
            }
            used[next_y][next_x] = 1;
            queue[rear++] = (Point){next_y, next_x};
        }
    }
    return is_peak;
}
int main(void)
{
    int cnt = 0;
    freopen("data.txt", "r", stdin);

    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &map[i][j]);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (used[i][j] == 0 && map[i][j] > 0)
            {
                cnt += bfs(i, j);
            }
        }
    }
    printf("%d", cnt);

    return 0;
}