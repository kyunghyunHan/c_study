/*
음식물 피하기
N M 음식물 쓰래기 의 개수 K

음식물이 떨어진 좌표


*/
#include <stdio.h>
#include <stdlib.h>

int n, m, k;
#define MAX 102
int map[MAX][MAX] = {0};
int f, r;
typedef struct Point
{
    int x;
    int y;
} Point;

Point queue[MAX * MAX];
int used[MAX][MAX];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
int cnt;
void bfs(int start_r, int start_c)
{
    cnt = 1;
    f = r = 0;

    queue[r++] = (Point){start_c, start_r};

    while (f < r)
    {
        Point current = queue[f++];
        used[current.y][current.x] = 1;

        for (int i = 0; i < 4; i++)
        {
            int next_x = current.x + dx[i];
            int next_y = current.y + dy[i];

            if (next_x < 1 || next_x > m ||
                next_y < 1 || next_y > n)
            {
                continue;
            }
            if (map[next_y][next_x] == 0)
            {
                continue;
            }
            if (map[next_y][next_x] == 1 && used[next_y][next_x] == 0)
            {

                queue[r++] = (Point){next_x, next_y};
                used[next_y][next_x] = 1;
                cnt++;
            }
        }
    }
}
int main(void)
{
    int answer = 0;
    cnt = 0;
    freopen("data.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < k; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        map[a][b] = 1;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (map[i][j] == 1 && used[i][j] == 0)
            {
                bfs(i, j);
                if (cnt > answer)
                {
                    answer = cnt;
                }
            }
        }
        // printf("\n");
    }

    printf("%d", answer);

    return 0;
}