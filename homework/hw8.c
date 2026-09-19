#include <stdio.h>
#include <stdlib.h>

#define MAX 102
#define INF 1000000000

typedef struct
{
    int y;
    int x;
} Point;

int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};

int arr[MAX][MAX];
int min_map[MAX][MAX];

Point queue[MAX * MAX * 100];

int front;
int rear;

void input(int n)
{
    for (int y = 1; y <= n; y++)
    {
        for (int x = 1; x <= n; x++)
        {
            scanf("%d", &arr[y][x]);
            min_map[y][x] = INF;
        }
    }
}

void start(int n)
{
    front = 0;
    rear = 0;

    for (int y = 1; y <= n; y++)
    {
        for (int x = 1; x <= n; x++)
        {
            if (y == 1 || y == n ||
                x == 1 || x == n)
            {
                min_map[y][x] =
                    arr[y][x] * arr[y][x];

                queue[rear++] = (Point){y, x};
            }
        }
    }
}

int main(void)
{
    int n;
    int target_x;
    int target_y;

    scanf("%d", &n);
    scanf("%d %d", &target_x, &target_y);

    input(n);
    start(n);

    while (front < rear)
    {
        Point current = queue[front++];

        int current_cost =
            min_map[current.y][current.x];

        for (int i = 0; i < 4; i++)
        {
            int next_y = current.y + dy[i];
            int next_x = current.x + dx[i];

            if (next_y < 1 || next_y > n ||
                next_x < 1 || next_x > n)
            {
                continue;
            }

            int move_cost;

            /* 오르막 */
            if (arr[next_y][next_x] -
                    arr[current.y][current.x] >
                0)
            {
                move_cost = (arr[next_y][next_x] -
                             arr[current.y][current.x]) *
                            (arr[next_y][next_x] -
                             arr[current.y][current.x]);
            }

            else
            {
                move_cost = arr[current.y][current.x] - arr[next_y][next_x];
            }

            int new_cost =
                current_cost + move_cost;

            if (new_cost < min_map[next_y][next_x])
            {
                min_map[next_y][next_x] = new_cost;

                queue[rear++] =
                    (Point){next_y, next_x};
            }
        }
    }

    printf("%d\n", min_map[target_x][target_y]);
    return 0;
}