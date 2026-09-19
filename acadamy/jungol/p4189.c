#include <stdio.h>
#include <stdlib.h>
#define MAX (1002)
typedef struct _Point
{
    int x;
    int y;

} Point;
int arr[MAX][MAX];
Point queue[MAX * MAX];
int rear, front;
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int main(void)
{
    int n, m;
    rear = front = 0;
    int r, c, s, k;
    scanf("%d %d", &n, &m);
    scanf("%d %d %d %d", &r, &c, &s, &k);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            arr[i][j] = 0;
        }
    }
    arr[r][c] = 1;
    // arr[s][k] = 0;
    queue[rear++] = (Point){r, c};

    while (front < rear)
    {
        Point current = queue[front++];

        if (current.x == s && current.y == k)
        {
            break;
        }

        for (int i = 0; i < 8; i++)
        {
            int next_x = current.x + dx[i];
            int next_y = current.y + dy[i];

            if (next_x < 1 || next_x > n || next_y < 1 || next_y > m)
            {
                continue;
            }
            if (arr[next_x][next_y] == 0)
            {
                arr[next_x][next_y] = arr[current.x][current.y] + 1;
                queue[rear++] = (Point){next_x, next_y};
            }
        }
    }
    printf("%d\n", arr[s][k]-1);
    return 0;
}
