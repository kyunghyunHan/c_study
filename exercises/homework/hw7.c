#include <stdio.h>

#define MAX 1001

typedef struct
{
    int r;
    int c;
} Point;

int dr[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dc[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int dist[MAX][MAX];
Point queue[MAX * MAX];

int bfs(int n, int m, Point start, Point target)
{
    int front = 0;
    int rear = 0;

    for (int r = 1; r <= n; r++)
    {
        for (int c = 1; c <= m; c++)
        {
            dist[r][c] = -1;
        }
    }

    dist[start.r][start.c] = 0;
    queue[rear++] = start;

    while (front < rear)
    {
        Point current = queue[front++];

        if (current.r == target.r && current.c == target.c)
        {
            return dist[current.r][current.c];
        }

        for (int i = 0; i < 8; i++)
        {
            int next_r = current.r + dr[i];
            int next_c = current.c + dc[i];

            if (next_r < 1 || next_r > n ||
                next_c < 1 || next_c > m)
            {
                continue;
            }

            if (dist[next_r][next_c] == -1)
            {
                dist[next_r][next_c] = dist[current.r][current.c] + 1;
                queue[rear++] = (Point){next_r, next_c};
            }
        }
    }

    return -1;
}

int main(void)
{
    int n, m;
    Point horse;
    Point soldier;

    if (scanf("%d %d", &n, &m) != 2)
        return 1;

    if (scanf("%d %d %d %d",
              &horse.r, &horse.c,
              &soldier.r, &soldier.c) != 4)
    {
        return 1;
    }

    printf("%d\n", bfs(n, m, horse, soldier));

    return 0;
}
