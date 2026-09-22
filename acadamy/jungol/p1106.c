/*
장기
M x n
*/

// /4~5개 문제

#include <stdio.h>
#include <stdlib.h>
#define MAX (102)
typedef struct _Point
{
    int x;
    int y;

} Point;
int n, m;
int r, c, s, k;
int front, rear;
Point quent[MAX * MAX];
int arr[MAX][MAX] = {0};

int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
void bfs(int start_r, int start_c)
{
    front = rear = 0;
    arr[start_r][start_c] = 0;
    quent[rear++] = (Point){start_c, start_r};

    while (front < rear)
    {

        Point current = quent[front++];
        if (current.x == k && current.y == s)
        {
            break;
        }

        for (int i = 0; i < 8; i++)
        {
            int next_x = current.x + dx[i];
            int next_y = current.y + dy[i];

            if (next_x < 1 || next_x > m || next_y < 1 || next_y > n)
            {
                continue;
            }

            if (arr[next_y][next_x] == -1)
            {
                arr[next_y][next_x] = arr[current.y][current.x] + 1;
                quent[rear++] = (Point){next_x, next_y};
            }
        }
    }
}
int main(void)
{

    // freopen("jungol.txt", "r", stdin);
    scanf("%d %d", &n, &m);

    scanf("%d %d %d %d", &r, &c, &s, &k);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            arr[i][j] = -1;
        }
    }
    bfs(r, c);

    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= m; j++)
    //     {
    //         printf("%d", arr[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("%d", arr[s][k]);

    return 0;
}