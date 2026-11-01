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
#define MAX (1002)
// GIGO

typedef struct
{
    // int z; // 높이
    int y; // 세로
    int x; // 가로
} Point;
int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};

Point queue[MAX * MAX];
int front = 0;
int rear = 0;

int arr[MAX][MAX] = {0};
void input(int n, int m)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
}

void start(int n, int m)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (arr[i][j] == 1)
            {
                queue[rear++] = (Point){i, j};
            }
        }
    }
}

int main(void)
{

    int m, n;
    scanf("%d %d", &m, &n);

    input(n, m);

    start(n, m);
    while (front < rear)
    {
        Point current = queue[front++];

        for (int i = 0; i < 4; i++)
        {
            int next_y = current.y + dy[i];
            int next_x = current.x + dx[i];

            if (
                next_y < 1 || next_y > n ||
                next_x < 1 || next_x > m)
            {
                continue;
            }

            if (arr[next_y][next_x] == 0)
            {
                arr[next_y][next_x] =
                    arr[current.y][current.x] + 1;
                queue[rear++] = (Point){next_y, next_x};
            }
            //queue에는 이미 들어가 있는거 부터
        }
    }
    int day = 1;

    for (int y = 1; y <= n; y++)
    {
        for (int x = 1; x <= m; x++)
        {
            if (arr[y][x] == 0)
            {
                printf("-1\n");
                return 0;
            }

            if (arr[y][x] > day)
                day = arr[y][x];
        }
    }
    printf("%d\n", day - 1);
    return 0;
}
