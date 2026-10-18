/*
백신
조직이 N행 M 열의 격자 형태
하나의 칸에 백신을 놓으면 격자 의 칸중 하나에 항체가 생성
이 항체는 현재 속해 있는 칸과 상하좌우로 인접


첫번쨰 사진이 실험 전 사진
두번쨰 사진이 실험 후 사진일수있다면 YES 그럴수 없다면 NO
*/
#include <stdio.h>
#include <stdlib.h>
int n, m;

#define MAX 32
typedef struct Point
{
    int y;
    int x;

} Point;
Point queue[MAX * MAX];
int rear, front;
int cmap[MAX][MAX];
int fmap[MAX][MAX];
int smap[MAX][MAX];
int used[MAX][MAX];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
int same(void)
{
    for (int y = 1; y <= n; y++)
    {
        for (int x = 1; x <= m; x++)
        {
            if (fmap[y][x] != smap[y][x])
                return 0;
        }
    }
    return 1;
}
void bfs(int start_y, int start_x)
{
    int before = fmap[start_y][start_x];
    int after = smap[start_y][start_x];

    front = rear = 0;
    used[start_y][start_x] = 1;
    fmap[start_y][start_x] = after;
    queue[rear++] = (Point){start_y, start_x};

    while (front < rear)
    {
        Point current = queue[front++];

        for (int i = 0; i < 4; i++)
        {
            int next_y = current.y + dy[i];
            int next_x = current.x + dx[i];

            if (next_y < 1 || next_y > n ||
                next_x < 1 || next_x > m)
                continue;

            if (used[next_y][next_x])
                continue;

            // 원래 시작 칸과 같은 값인 칸으로만 퍼짐
            if (fmap[next_y][next_x] != before)
                continue;

            used[next_y][next_x] = 1;
            fmap[next_y][next_x] = after;
            queue[rear++] = (Point){next_y, next_x};
        }
    }
}
int main(void)
{
    freopen("data.txt", "r", stdin);
    scanf("%d %d", &n, &m);

    for (int y = 1; y <= n; y++)
        for (int x = 1; x <= m; x++)
            scanf("%d", &fmap[y][x]);

    for (int y = 1; y <= n; y++)
        for (int x = 1; x <= m; x++)
            scanf("%d", &smap[y][x]);

    for (int y = 1; y <= n; y++)
    {
        for (int x = 1; x <= m; x++)
        {
            if (fmap[y][x] != smap[y][x])
            {
                bfs(y, x);
                printf("%s\n", same() ? "YES" : "NO");
                return 0;
            }
        }
    }

    printf("YES\n");
    return 0;
}