#include <stdio.h>

#define MAX 102
#define INF 1000000000

typedef struct Point
{
    int y;
    int x;
} Point;

int map[MAX][MAX];

int price1[MAX][MAX];
int price2[MAX][MAX];

Point queue1[MAX * MAX];
Point queue2[MAX * MAX];

int n, t;

Point start;
Point end;

int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, -1, 1};

int bfs(void)
{
    int (*cur)[MAX] = price1;
    int (*next)[MAX] = price2;

    Point *cur_queue = queue1;
    Point *next_queue = queue2;

    // 초기화
    for (int y = 1; y <= n; y++)
    {
        for (int x = 1; x <= n; x++)
        {
            cur[y][x] = INF;
            next[y][x] = INF;
        }
    }

    cur[start.y][start.x] = 0;

    int cur_size = 1;

    cur_queue[0] = start;

    int answer = INF;

    // time = 지금 이동해서 도착하게 되는 시간
    for (int time = 1; time <= t; time++)
    {
        int next_size = 0;

        /*
         * 이전 time에서 사용했던 next 배열의 좌표만
         * INF로 초기화한다.
         *
         * 전체 n*n을 초기화하지 않음.
         */
        for (int i = 0; i < cur_size; i++)
        {
            // 여기서는 cur를 건드리면 안 됨
        }

        for (int q = 0; q < cur_size; q++)
        {
            Point current = cur_queue[q];

            int current_price =
                cur[current.y][current.x];

            for (int i = 0; i < 4; i++)
            {
                int ny = current.y + dy[i];
                int nx = current.x + dx[i];

                // 범위
                if (ny < 1 || ny > n ||
                    nx < 1 || nx > n)
                {
                    continue;
                }

                // 건물
                if (map[ny][nx] == 0)
                {
                    continue;
                }

                int new_price = current_price;

                // 일반 칸이면 일사량 추가
                if (map[ny][nx] > 0)
                {
                    new_price += map[ny][nx];
                }

                // 이미 찾은 답보다 비싸면 필요 없음
                if (new_price >= answer)
                {
                    continue;
                }

                // 도착
                if (map[ny][nx] == -2)
                {
                    if (new_price < answer)
                    {
                        answer = new_price;
                    }

                    continue;
                }

                /*
                 * 정확히 time분에 (ny,nx)에 오는
                 * 최소 비용만 남긴다.
                 */
                if (new_price < next[ny][nx])
                {
                    /*
                     * 이번 시간에 처음 들어온 좌표라면
                     * 큐에는 한 번만 넣는다.
                     */
                    if (next[ny][nx] == INF)
                    {
                        next_queue[next_size++] =
                            (Point){ny, nx};
                    }

                    next[ny][nx] = new_price;
                }
            }
        }

        /*
         * 지금 cur 배열에서 사용했던 값들은
         * 다음에 next 배열로 재사용되므로 INF로 초기화.
         *
         * 전체 n*n이 아니라 큐에 있던 것만 초기화.
         */
        for (int i = 0; i < cur_size; i++)
        {
            int y = cur_queue[i].y;
            int x = cur_queue[i].x;

            cur[y][x] = INF;
        }

        // 배열 swap
        int (*temp_price)[MAX] = cur;
        cur = next;
        next = temp_price;

        // 큐 swap
        Point *temp_queue = cur_queue;
        cur_queue = next_queue;
        next_queue = temp_queue;

        cur_size = next_size;

        // 더 갈 곳 없음
        if (cur_size == 0)
        {
            break;
        }
    }

    if (answer == INF)
    {
        return -1;
    }

    return answer;
}

int main(void)
{
    freopen("data.txt", "r", stdin);

    scanf("%d %d", &n, &t);

    for (int y = 1; y <= n; y++)
    {
        for (int x = 1; x <= n; x++)
        {
            scanf("%d", &map[y][x]);

            if (map[y][x] == -1)
            {
                start = (Point){y, x};
            }

            if (map[y][x] == -2)
            {
                end = (Point){y, x};
            }
        }
    }

    printf("%d\n", bfs());

    return 0;
}