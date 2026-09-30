/*
빨강과 검정


*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 22
typedef struct Point
{
    int y;
    int x;
} Point;
Point queue[MAX * MAX];
int used[MAX][MAX];
int map[MAX][MAX];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
int w, h;
int start_y, start_x;
int front, rear;
int cnt;
void bfs(int start_y, int start_x)
{
    front = 0;
    rear = 0;
    cnt = 1;
    used[start_y][start_x] = 1;
    queue[rear++] = (Point){start_y, start_x};
    while (front < rear)
    {
        Point current = queue[front++];

        for (int i = 0; i < 4; i++)
        {
            int next_y = current.y + dy[i];
            int next_x = current.x + dx[i];

            if (next_x < 1 || next_x > w || next_y < 1 || next_y > h)
            {
                continue;
            }
            if (used[next_y][next_x] == 1)
            {
                continue;
            }
            if (map[next_y][next_x] == 2)
            {
                continue;
            }
            used[next_y][next_x] = 1;
            queue[rear++] = (Point){next_y, next_x};
            map[next_y][next_x] = map[current.y][current.x] + 1;
            cnt++;
        }
    }
}
int main(void)
{

    freopen("data.txt", "r", stdin);
    scanf("%d %d", &w, &h);
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            char s;
            scanf(" %c", &s);

            if (s == '.')
            {
                map[i][j] = 0;
            }
            if (s == '#')
            {
                map[i][j] = 2;
            }

            if (s == '@')
            {
                map[i][j] = 1;
                start_x = j;
                start_y = i;
            }
        }
    }

    bfs(start_y, start_x);
    printf("%d", cnt);
    return 0;
}