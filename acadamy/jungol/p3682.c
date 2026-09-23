/*
구름

정올시는 남북 방향으로 H 킬로미터
동서 방향으로 W 킬로미터

H * W 개 의 1킬로미터


소구획을 i j
각 소구획은 구름이 있거나 없거나

모든 구름은 1분이 지날떄마다 동쪽으로 1킬리미터 이돛

수호획에 구름이 있다 0
몇분이 지나도 소구획 상공에 구름이 안온다 -1
처음에 구름이 있으면 0
1분뒤
2분뒤
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct Point
{
    int r;
    int c;
} Point;
Point queue[MAX * MAX];
int used[MAX][MAX];
int arr[MAX][MAX];
int rear, front;
int h, w;

void bfs(void)
{

    while (front < rear)
    {

        Point current = queue[front++];
        int next = current.c + 1;

        if (next < 0 || next >= w)
        {
            continue;
        }
        if (used[current.r][next] == 1)
        {
            continue;
        }
        arr[current.r][next] = arr[current.r][current.c] + 1;
        queue[rear++] = (Point){current.r, next};
    }
    return;
}
int main(void)
{
    rear = 0;
    front = 0;
    freopen("jungol.txt", "r", stdin);

    scanf("%d %d", &h, &w);

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            char s;
            scanf(" %c", &s);
            if (s == 'c')
            {
                arr[i][j] = 0;
                used[i][j] = 1;
                queue[rear++] = (Point){i, j};
            }
            else
            {
                arr[i][j] = -1;
            }
        }
    }

    bfs();

    for (int i = 0; i < h; i++)
    {

        for (int j = 0; j < w; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}