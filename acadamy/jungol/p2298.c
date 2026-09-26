/*

BFS는 넓이
*/
#include <stdio.h>
#include <stdlib.h>
int n;
#define MAX 102
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
int map[MAX][MAX];
int used[MAX][MAX];
int rear, front;
int answer;
#include <string.h>
typedef struct Point
{
    int x;
    int y;
} Point;
Point queue[MAX * MAX];

void bfs(int start_x, int start_y, int h)
{
    front = rear = 0;
    used[start_y][start_x] = 1;
    queue[rear++] = (Point){start_x, start_y};

    while (front < rear)
    {

        Point currnet = queue[front++];

        for (int i = 0; i < 4; i++)
        {
            int next_x = currnet.x + dx[i];
            int next_y = currnet.y + dy[i];

            if (next_x < 1 || next_x > n || next_y < 1 || next_y > n)
            {
                continue;
            }

            if (used[next_y][next_x] == 1)
            {
                continue;
            }
            if (map[next_y][next_x] <= h)
            {
                continue;
            }
            used[next_y][next_x] = 1;
            queue[rear++] = (Point){next_x, next_y};
        }
    }
}
int main(void)
{
    rear = front = 0;

    freopen("data.txt", "r", stdin);
    scanf("%d", &n);
    // 맵챙고
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &map[i][j]);
        }
    }
    // 높이마다 검사
    for (int h = 0; h <= 100; h++)
    {
        // 0으로 초기화
        memset(used, 0, sizeof(used));
        int cnt = 0;
        // 카운터  처음부터검산
        //카운터는 몇번 bfs햇나
        for (int y = 1; y <= n; y++)
        {
            for (int x = 1; x <= n; x++)
            {
                // h보다 크고 used가 0이면검사
                if (map[y][x] > h &&
                    used[y][x] == 0)
                {
                    //카운터 증가
                    cnt++;
                    bfs(x, y, h);
                }
            }
        }
        if (cnt > answer)
            answer = cnt;
        // answer와 cnt 비교
    }
    printf("%d", answer);
    return 0;
}