/*
우회전

*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 102
typedef struct Point
{
    int y;
    int x;
    int dir;
    int dist;
} Point;
Point queue[MAX * MAX * 4];
int front, rear;
int n, m;
int ans;
// 위 -> 오른쪽 -> 아래 -> 왼쪽: 인덱스에 1을 더하면 우회전
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};
int used[MAX][MAX][4];
char map[MAX][MAX];

void bfs(int start_y, int start_x)
{
    front = rear = 0;
    for (int d = 0; d < 4; d++)
    {
        queue[rear++] = (Point){start_y, start_x, d, 0};
        used[start_y][start_x][d] = 1;
    }
    while (front < rear)
    {
        Point current = queue[front++];

        if (map[current.y][current.x] == 'B')
        {
            ans = current.dist;
            return;
        }
        for (int i = 0; i < 2; i++)
        {
            int nd = (current.dir + i) % 4;

            int ny = current.y + dy[nd];
            int nx = current.x + dx[nd];

            if (ny < 1 || ny > n || nx < 1 || nx > m)
                continue;

            if (map[ny][nx] == 'X')
                continue;

            if (used[ny][nx][nd] == 1)
                continue;

            used[ny][nx][nd] = 1;

            queue[rear++] = (Point){
                ny, nx, nd, current.dist + 1};
        }
    }
}
int main(void)
{
    freopen("data.txt", "r", stdin);
    int start_y, start_x;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf(" %c", &map[i][j]);
            if (map[i][j] == 'A')
            {
                start_y = i;
                start_x = j;
            }
        }
    }
    bfs(start_y, start_x);

    printf("%d", ans == 0 ? -1 : ans);

    return 0;
}
