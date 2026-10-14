/*
호수 찾기
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 102
typedef struct Point
{
    int y;
    int x;

} Point;
Point queue[MAX * MAX];
int rear, front;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
int used[MAX][MAX];
int map[MAX][MAX] = {0};
int n, m, k;
int cnt;
void bfs(int start_y, int start_x)
{

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
            if (used[next_y][next_x] == 1 || map[next_y][next_x] == 0)
            {
                continue;
            }

            used[next_y][next_x] = 1;
            queue[rear++] = (Point){next_y, next_x};
            cnt++;
        }
    }
    return;
}
int main(void)
{
    rear = 0;
    front = 0;
    int res = 0;
    freopen("data.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < k; i++)
    {
        int k1, k2;
        scanf("%d %d", &k1, &k2);
        map[k1][k2] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (used[i][j] == 0 && map[i][j] == 1)
            {
                cnt = 0;
                bfs(i, j);
                if (cnt > res)
                {
                    res = cnt;
                }
            }
        }
    }
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= m; j++)
    //     {
    //         printf(" %d", map[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("%d", res);
    return 0;
}