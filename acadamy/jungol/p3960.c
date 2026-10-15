/*
성난 소들


       3 4  5  6   8     13
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 102

typedef struct Point
{
    int x; // 좌표가 아닌 소의 번호
    int b;
} Point;
int n;
int used[MAX];
int pos[MAX];
Point queue[MAX];
int front, rear;

int cnt;
void bfs(int start)
{
    used[start] = 1;
    queue[rear++] = (Point){start, 1};

    while (front < rear)
    {
        Point current = queue[front++];

        for (int i = 0; i < n; i++)
        {
            if (used[i] == 1)
            {
                continue;
            }
            // 현재 폭발하는 소와의 실제 좌표 차이를 확인
            if (abs(pos[i] - pos[current.x]) > current.b)
            {
                continue;
            }
            cnt++;
            used[i] = 1;
            queue[rear++] = (Point){i, current.b + 1};
        }
    }
}
int main(void)
{
    freopen("data.txt", "r", stdin);
    int res = 0;
    if (scanf("%d", &n) != 1 || n < 1 || n >= MAX)
        return 0;

    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &pos[i]) != 1)
            return 0;
    }

    for (int i = 0; i < n; i++) // 모든 소를 시작점으로 시도
    {
        for (int j = 0; j < n; j++)
        {
            used[j] = 0;
        }

        front = rear = 0;
        cnt = 1; // 처음 폭발시키는 소도 포함

        bfs(i);

        if (res < cnt)
        {
            res = cnt;
        }
    }
    printf("%d\n", res);
    return 0;
}
