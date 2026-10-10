/*
나쁜 풀
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 1002
int r, c;

typedef struct Point
{
    int r;
    int c;
} Point;
int map[MAX][MAX];
int used[MAX][MAX];
int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
int dx[8] = {0, 0, 1, -1, -1, -1, 1, 1};
int rear, front;
int cnt;
Point queue[MAX * MAX];
void bsf(int start_y, int start_x)
{
    front = 0;
    rear = 0;
    used[start_y][start_x] = 1;
    queue[rear++] = (Point){start_y, start_x};

    while (front < rear)
    {
        Point current = queue[front++];
        for (int i = 0; i < 8; i++)
        {
            int next_y = current.r + dy[i];
            int next_x = current.c + dx[i];
            if (next_x < 1 || next_x > c || next_y < 1 || next_y > r)
            {
                continue;
            }
            if (map[next_y][next_x] == 0 || used[next_y][next_x] == 1)
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
    cnt = 0;
    freopen("data.txt", "r", stdin);
    scanf("%d %d", &r, &c);
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            scanf("%d", &map[i][j]);
        }
    }
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            if (map[i][j] > 0 && used[i][j] == 0)
            {
                bsf(i, j);
                cnt++;
            }
        }
    }
    printf("%d", cnt);
    return 0;
}