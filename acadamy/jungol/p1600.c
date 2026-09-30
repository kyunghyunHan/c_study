/* 빙산 */

#include <stdio.h>
#include <string.h>

#define MAX 302

int n, m; // n = 행(y), m = 열(x)

typedef struct Point
{
    int y;
    int x;
} Point;

Point queue[MAX * MAX];

int MAP[MAX][MAX];
int used[MAX][MAX];
int melt_map[MAX][MAX];

int front, rear;

int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, -1, 1};

/*
    BFS
    연결되어 있는 빙산 한 덩어리를 방문한다.
*/
void bfs(int start_y, int start_x)
{
    front = rear = 0;

    used[start_y][start_x] = 1;
    queue[rear++] = (Point){start_y, start_x};

    while (front < rear)
    {
        Point current = queue[front++];

        for (int i = 0; i < 4; i++)
        {
            int next_y = current.y + dy[i];
            int next_x = current.x + dx[i];

            // 범위 검사
            // y는 1 ~ n
            // x는 1 ~ m
            if (next_y < 1 || next_y > n ||
                next_x < 1 || next_x > m)
            {
                continue;
            }

            // 이미 방문
            if (used[next_y][next_x] == 1)
            {
                continue;
            }

            // 바다는 이동하지 않음
            if (MAP[next_y][next_x] <= 0)
            {
                continue;
            }

            used[next_y][next_x] = 1;

            queue[rear++] = (Point){
                next_y,
                next_x};
        }
    }
}

/*
    빙산을 1년 녹인다.
*/
void melt(void)
{
    memset(melt_map, 0, sizeof(melt_map));

    /*
        먼저 각 빙산이 얼마나 녹아야 하는지 계산

        여기서는 MAP을 아직 변경하지 않는다.
    */
    for (int y = 1; y <= n; y++)
    {
        for (int x = 1; x <= m; x++)
        {
            // 바다라면 검사할 필요 없음
            if (MAP[y][x] <= 0)
            {
                continue;
            }

            // 상하좌우 검사
            for (int i = 0; i < 4; i++)
            {
                int next_y = y + dy[i];
                int next_x = x + dx[i];

                if (next_y < 1 || next_y > n ||
                    next_x < 1 || next_x > m)
                {
                    continue;
                }

                // 주변이 바다라면
                if (MAP[next_y][next_x] == 0)
                {
                    melt_map[y][x]++;
                }
            }
        }
    }

    /*
        모든 감소량을 구한 뒤
        실제 MAP을 한꺼번에 변경
    */
    for (int y = 1; y <= n; y++)
    {
        for (int x = 1; x <= m; x++)
        {
            if (MAP[y][x] <= 0)
            {
                continue;
            }

            MAP[y][x] -= melt_map[y][x];

            // 음수가 되면 0
            if (MAP[y][x] < 0)
            {
                MAP[y][x] = 0;
            }
        }
    }
}

int main(void)
{
    freopen("data.txt", "r", stdin);

    /*
        N = 행
        M = 열

        예:
        5 7

        n = 5
        m = 7
    */
    scanf("%d %d", &n, &m);

    /*
        y : 1 ~ n
        x : 1 ~ m
    */
    for (int y = 1; y <= n; y++)
    {
        for (int x = 1; x <= m; x++)
        {
            scanf("%d", &MAP[y][x]);
        }
    }

    int year = 0;

    while (1)
    {
        // 새로운 해에 다시 방문 검사
        memset(used, 0, sizeof(used));

        int cnt = 0;

        /*
            현재 빙산이 몇 덩어리인지 검사
        */
        for (int y = 1; y <= n; y++)
        {
            for (int x = 1; x <= m; x++)
            {
                // 빙산이고 아직 방문하지 않았다면
                if (MAP[y][x] > 0 &&
                    used[y][x] == 0)
                {
                    /*
                        여기서 BFS 한 번 실행하면
                        연결된 빙산 한 덩어리를 전부 방문
                    */
                    bfs(y, x);

                    cnt++;
                }
            }
        }

        /*
            2덩어리 이상이면 분리된 것
        */
        if (cnt >= 2)
        {
            printf("%d\n", year);
            return 0;
        }

        /*
            분리되기 전에 전부 녹아버림
        */
        if (cnt == 0)
        {
            printf("0\n");
            return 0;
        }

        // 아직 한 덩어리이므로 1년 녹인다.
        melt();

        year++;
    }

    return 0;
}