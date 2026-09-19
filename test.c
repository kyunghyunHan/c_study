#include <stdio.h>

#define MAX 1001

typedef struct
{
    int x;
    int y;
} Point;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int box[MAX][MAX];
Point queue[MAX * MAX];

int main(void)
{
    int m, n;
    int front = 0;
    int rear = 0;
    int answer = 0;

    /* 입력은 가로(M), 세로(N) 순서이다. */
    if (scanf("%d %d", &m, &n) != 2)
    {
        return 1;
    }

    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= m; y++)
        {
            scanf("%d", &box[x][y]);

            /* 처음부터 익은 모든 토마토를 시작점으로 넣는다. */
            if (box[x][y] == 1)
            {
                queue[rear++] = (Point){x, y};
            }
        }
    }

    /* 여러 시작점에서 동시에 진행하는 BFS */
    while (front < rear)
    {
        Point current = queue[front++];

        for (int i = 0; i < 4; i++)
        {
            int next_x = current.x + dx[i];
            int next_y = current.y + dy[i];

            if (next_x < 1 || next_x > n ||
                next_y < 1 || next_y > m)
            {
                continue;
            }

            /* 안 익은 토마토만 새로 익힌다. */
            if (box[next_x][next_y] == 0)
            {
                box[next_x][next_y] = box[current.x][current.y] + 1;
                queue[rear++] = (Point){next_x, next_y};

                /* 저장된 값은 1일부터 시작하므로 1을 뺀다. */
                answer = box[next_x][next_y] - 1;
            }
        }
    }

    /* BFS 후에도 0이 남으면 익을 수 없는 토마토가 있다. */
    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= m; y++)
        {
            if (box[x][y] == 0)
            {
                printf("-1\n");
                return 0;
            }
        }
    }

    printf("%d\n", answer);

    return 0;
}
