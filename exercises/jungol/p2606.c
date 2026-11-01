/*
토마토 (초)

입력파일 첫줄 정수 N M H

1은 익은 토마토
정수 0 은 익지 않은 토마토
정수 -1 은 토마토가 없음

위아래

저장될떄부터 모두  익어있으면 0
토마토가 모두 익지 못하면 -1
익을떄까지 몇 일걸리나

*/
#include <stdio.h>
#include <stdlib.h>
#define MAX (102)
// GIGO

typedef struct
{
    int z; // 높이
    int y; // 세로
    int x; // 가로
} Point;
int dz[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dx[6] = {0, 0, 0, 0, 1, -1};

Point queue[MAX * MAX * MAX];
int front = 0;
int rear = 0;

int arr[MAX][MAX][MAX] = {0};
void input(int n, int m, int h)
{
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= m; k++)
            {
                scanf("%d", &arr[i][j][k]);
            }
        }
    }
}

void start(int n, int m, int h)
{
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= m; k++)
            {
                if (arr[i][j][k] == 1)
                {
                    queue[rear++] = (Point){i, j, k};
                }
            }
        }
    }
}
void print_arr(int arr[][MAX][MAX], int m, int n, int h)
{
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= m; k++)
            {
                printf("%d ", arr[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}
int main(void)
{

    int m, n, h;
    scanf("%d %d %d", &m, &n, &h);

    input(n, m, h);

    start(n, m, h);
    while (front < rear)
    {
        Point current = queue[front++];

        for (int i = 0; i < 6; i++)
        {
            int next_z = current.z + dz[i];
            int next_y = current.y + dy[i];
            int next_x = current.x + dx[i];

            if (next_z < 1 || next_z > h ||
                next_y < 1 || next_y > n ||
                next_x < 1 || next_x > m)
            {
                continue;
            }

            if (arr[next_z][next_y][next_x] == 0)
            {
                arr[next_z][next_y][next_x] =
                    arr[current.z][current.y][current.x] + 1;
                queue[rear++] = (Point){next_z, next_y, next_x};
            }
        }
    }
    int day = 1;

    for (int z = 1; z <= h; z++)
    {
        for (int y = 1; y <= n; y++)
        {
            for (int x = 1; x <= m; x++)
            {
                if (arr[z][y][x] == 0)
                {
                    printf("-1\n");
                    return 0;
                }

                if (arr[z][y][x] > day)
                    day = arr[z][y][x];
            }
        }
    }

    printf("%d\n", day - 1);
    return 0;
}
