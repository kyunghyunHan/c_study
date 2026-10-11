/*
풀뭉치
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 102
typedef struct Point
{
    int r;
    int c;
} Point;
Point queue[MAX * MAX];
int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, -1, 1};
int map[MAX][MAX];
int used[MAX][MAX];
int r, c;
int front, rear;

void bfs(int start_y, int start_x)
{
    used[start_y][start_x] = 1;
    queue[rear++] = (Point){start_y, start_x};

    while (front < rear)
    {
        Point current = queue[front++];

        for (int i = 0; i < 4; i++)
        {
            int next_y = current.r + dy[i];
            int next_x = current.c + dx[i];

            if (next_y < 1 || next_y > r || next_x < 1 || next_x > c)
            {
                continue;
            }
            if (map[next_y][next_x] == 0)
            {
                continue;
            }
            if (used[next_y][next_x] == 1)
            {
                continue;
            }

            used[next_y][next_x] = 1;
            queue[rear++] = (Point){next_y, next_x};
        }
    }
}
int main(void)
{
    front = 0;
    rear = 0;
    int cnt = 0;
    freopen("data.txt", "r", stdin);
    scanf("%d %d", &r, &c);
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            int c;
            scanf(" %c", &c);
            if (c == '#')
            {
                map[i][j] = 1;
            }
            else
            {
                map[i][j] = 0;
            }
        }
    }

    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            if (used[i][j] == 0 && map[i][j] == 1)
            {
                bfs(i, j);
                cnt++;
            }
        }
    }
    printf("%d", cnt);

    return 0;
}