/*
저글링

방사능에 오염된 저글링은 3초 후에 죽음
열과 행
100x 100

1은 저글링 위치 0은 없는곳
시작은 1

출력
몇초걸리는지
남은 저글링 수
*/

typedef struct _Point
{
    int x;
    int y;

} Point;
#include <stdio.h>
#include <stdlib.h>
#define MAX (102)
Point queue[MAX * MAX];
int arr[MAX][MAX];
int used[MAX][MAX];
int time;
int r, c;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
int rear, front;
void bfs(int x, int y)
{
    front = 0;
    rear = 0;
    time = 1;
    // 첫값 추가
    queue[rear++] = (Point){x, y};
    while (front < rear)
    {
        Point current = queue[front++];
        for (int i = 0; i < 4; i++)
        {
            int next_x = current.x + dc[i];
            int next_y = current.y + dr[i];

            if (next_x < 1 || next_x > c || next_y < 1 || next_y > r)
            {
                continue;
            }
            if (arr[next_x][next_y] == 1)
            {
                arr[next_x][next_y] = arr[current.x][current.y] + 1;
                queue[rear++] = (Point){next_x, next_y};
            }
        }
        time++;
    }
}
int main(void)
{
    freopen("jungol.txt", "r", stdin);

    scanf("%d %d", &c, &r);

    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    int target_x, target_y;
    scanf("%d %d", &target_x, &target_y);
    bfs(target_x, target_y);

    printf("%d", time);
    return 0;
}