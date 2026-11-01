/*
문제은행

*/
#include <stdio.h>

#define MAX 102

typedef struct Point
{
    int y;
    int x;
} Point;
Point queue[MAX * MAX];
int rear, front;
int used[MAX][MAX];
int dist[MAX][MAX];
int map[MAX][MAX] = {0};
int x, y;
int start_y, start_x, end_y, end_x;
int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, -1, 1};
void bfs(int start_y, int start_x)
{
    used[start_y][start_x] = 1;
    // dist[start_y][start_x] = 1;
    queue[rear++] = (Point){start_y, start_x};

    while (front < rear)
    {
        Point current = queue[front++];

        if (current.y == end_y && current.x == end_x)
        {
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            int next_x = current.x + dx[i];
            int next_y = current.y + dy[i];

            if (next_x < 1 || next_x > x ||
                next_y < 1 || next_y > y)
            {
                continue;
            }
            if (used[next_y][next_x] == 1)
            {
                continue;
            }
            if (map[next_y][next_x] == 1)
            {
                continue;
            }

            queue[rear++] = (Point){next_y, next_x};
            used[next_y][next_x] = 1;

            dist[next_y][next_x] = dist[current.y][current.x] + 1;

            // if (dist[next_y][next_x] != 0)
            // {
            //     if (dist[next_y][next_x] > dist[current.y][current.x] + 1)
            //     {
            //         dist[next_y][next_x] = dist[current.y][current.x] + 1;
            //     }
            // }
            // else
            // {
            //     dist[next_y][next_x] = 1;
            // }
        }
    }
}
int main(void)
{
    rear = front = 0;

    freopen("./sandbox/data.txt", "r", stdin);
    scanf("%d %d", &x, &y);
    scanf("%d %d %d %d", &start_x, &start_y, &end_x, &end_y);

    for (int i = 1; i <= y; i++)
    {
        for (int j = 1; j <= x; j++)
        {
            scanf("%1d", &map[i][j]);
        }
    }

    bfs(start_y, start_x);

    printf("%d\n", dist[end_y][end_x]);

    return 0;
}