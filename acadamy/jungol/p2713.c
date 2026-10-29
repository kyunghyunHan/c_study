
/*
생일 선물 사기

2 : 시작 위치
3 : 최종 목적지
4 : 선물을 살 수 있는 위치
1 : 벽
0 : 이동 가능한 칸

목표: 2 → 4 → 3 최단 거리
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX 1002

int map[MAX][MAX];

int dist2[MAX][MAX]; // 2에서 출발한 최단 거리
int dist3[MAX][MAX]; // 3에서 출발한 최단 거리

typedef struct Point
{
    int y;
    int x;
} Point;

Point queue[MAX * MAX];

int rear, front;
int w, h;

int start_y, start_x;
int end_y, end_x;

int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, -1, 1};

/* BFS */
void bfs(int y, int x, int used[MAX][MAX])
{
    // 큐 초기화
    front = rear = 0;

    // 시작점 방문 처리
    used[y][x] = 1;
    queue[rear++] = (Point){y, x};

    while (front < rear)
    {
        Point current = queue[front++];

        for (int i = 0; i < 4; i++)
        {
            int next_y = current.y + dy[i];
            int next_x = current.x + dx[i];

            // 범위 확인
            if (next_y < 1 || next_y > h ||
                next_x < 1 || next_x > w)
            {
                continue;
            }

            // 방문 여부 확인
            if (used[next_y][next_x] != 0)
            {
                continue;
            }

            // 벽 확인
            if (map[next_y][next_x] == 1)
            {
                continue;
            }

            // 현재 거리 + 1
            used[next_y][next_x] =
                used[current.y][current.x] + 1;

            // 큐 삽입
            queue[rear++] = (Point){next_y, next_x};
        }
    }
}

int main(void)
{
    // 로컬 테스트용. 온라인 제출 시 제거
    freopen("data.txt", "r", stdin);

    scanf("%d %d", &w, &h);

    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            scanf("%d", &map[i][j]);

            if (map[i][j] == 2)
            {
                start_y = i;
                start_x = j;
            }

            if (map[i][j] == 3)
            {
                end_y = i;
                end_x = j;
            }
        }
    }

    // 2에서 모든 칸까지 최단 거리
    bfs(start_y, start_x, dist2);

    // 3에서 모든 칸까지 최단 거리
    bfs(end_y, end_x, dist3);

    int min = INT_MAX;

    // 모든 선물 위치(4) 확인
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            if (map[i][j] == 4)
            {
                // 도달할 수 없는 위치 제외
                if (dist2[i][j] == 0 ||
                    dist3[i][j] == 0)
                {
                    continue;
                }

                // 2 → 4 → 3
                int total = (dist2[i][j] - 1)
                          + (dist3[i][j] - 1);

                if (total < min)
                {
                    min = total;
                }
            }
        }
    }

    if (min == INT_MAX)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n", min);
    }

    return 0;
}
