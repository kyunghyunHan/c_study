/*간단한 직사각형 문제 */
#include <stdio.h>
#include <stdlib.h>
int front, rear;
#define MAX 103
char map[MAX][MAX];
int used[MAX][MAX];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
int n, m;
typedef struct Point
{
    int y;
    int x;
} Point;
Point queue[MAX * MAX];
void bfs(int start_y, int start_x)
{
    used[start_y][start_x] = 1;
    queue[rear++] = (Point){start_y, start_x};
    while (front < rear)
    {
        Point current = queue[front++];
        for (int i = 0; i < 4; i++)
        {
            int next_y = current.y + dy[i];
            int next_x = current.x + dx[i];

            if (next_y < 1 || next_y > n || next_x < 1 || next_x > m)
            {
                continue;
            }
            if (used[next_y][next_x] == 1)
            {
                continue;
            }
            if (map[next_y][next_x] == '.')
            {
                continue;
            }
            used[next_y][next_x] = 1;
            queue[rear++] = (Point){next_y, next_x};
        }
    }
}
void input_map()
{
    freopen("data.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf(" %c", &map[i][j]);
        }
    }
}
int main(void)
{
    int cnt = 0;
    front = rear = 0;
    input_map();
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (used[i][j] == 0 && map[i][j] == '*')
            {
                cnt++;
                bfs(i, j);
            }
        }
    }
    printf("%d",cnt);
    return 0;
}