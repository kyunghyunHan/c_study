/*
늑대와양
. 빈필드
# 울타리
o 는 양
v 는 늑대

상하좌우
영역안에 늑대의 수보다 양이 많으면 이김
그렇지 않으면

살아있는 양과 늑대의 양을
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 252
int arr[MAX][MAX];
int used[MAX][MAX];
typedef struct Point
{
    int y;
    int x;
} Point;
Point queue[MAX * MAX];
int front, rear;
int r, c;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
int ra, rb, a, b;
void bfs(int start_y, int start_x)
{
    used[start_y][start_x] = 1;
    front = 0;
    rear = 0;
    a = 0;
    b = 0;

    queue[rear++] = (Point){start_y, start_x};

    while (front < rear)
    {
        Point current = queue[front++];
        if (arr[current.y][current.x] == 2)
            a++;

        if (arr[current.y][current.x] == -1)
            b++;

        for (int i = 0; i < 4; i++)
        {
            int next_x = current.x + dx[i];
            int next_y = current.y + dy[i];

            if (next_x < 1 || next_x > c ||
                next_y < 1 || next_y > r)
            {
                continue;
            }
            if (used[next_y][next_x] == 1 || arr[next_y][next_x] == 1)
            {
                continue;
            }

            used[next_y][next_x] = 1;
            queue[rear++] = (Point){next_y, next_x};
        }
    }
    if (a > b)
    {
        b = 0;
    }
    else
    {
        a = 0;
    }
}
int main(void)
{

    freopen("data.txt", "r", stdin);
    scanf("%d %d", &r, &c);
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            char s;
            scanf(" %c", &s);
            if (s == '#')
            {
                arr[i][j] = 1;
                used[i][j] = 1;
            }
            else if (s == 'v')
            {
                arr[i][j] = -1;
            }
            else if (s == 'o')
            {
                arr[i][j] = 2;
            }
        }
    }

    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            if (used[i][j] == 0)
            {
                a = 0;
                b = 0;
                used[i][j] = 1;
                bfs(i, j);
                ra += a;
                rb += b;
            }
        }
    }
    printf("%d %d", ra, rb);
    return 0;
}