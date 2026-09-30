#include <stdio.h>
#include <stdlib.h>

#define MAX_CELL 2000005

int R, C;

/*
1차원으로 격자를 저장

(y, x)의 위치:
y * C + x
*/
char map[MAX_CELL];

/*
방문 여부
*/
unsigned char used[MAX_CELL];

/*
BFS에서는 좌표 두 개를 저장할 필요 없이
1차원 index만 저장
*/
int queue[MAX_CELL];

int front;
int rear;

int total_dot;

/*
(y, x) → 1차원 index
*/
int pos(int y, int x)
{
    return y * C + x;
}

int bfs(void)
{
    front = 0;
    rear = 0;

    /*
    C열의 모든 '.'을 시작점으로 넣는다.

    여기서는 좌표를 0부터 사용하므로
    마지막 열 = C - 1
    */
    for (int y = 0; y < R; y++)
    {
        int p = pos(y, C - 1);

        if (map[p] == '.')
        {
            used[p] = 1;
            queue[rear++] = p;
        }
    }

    /*
    시작점 자체도 도체 하나를 사용
    */
    int remain = 1;

    while (front < rear)
    {
        /*
        현재 BFS 레벨의 개수
        */
        int level_count = rear - front;

        while (level_count--)
        {
            int current = queue[front++];

            /*
            1차원 index를 다시 y, x로 변환
            */
            int y = current / C;
            int x = current % C;

            /*
            1열 도착

            0-based이므로 x == 0
            */
            if (x == 0)
            {
                return remain;
            }

            /*
            위
            */
            if (y > 0)
            {
                int next = current - C;

                if (map[next] == '.' &&
                    used[next] == 0)
                {
                    used[next] = 1;
                    queue[rear++] = next;
                }
            }

            /*
            아래
            */
            if (y + 1 < R)
            {
                int next = current + C;

                if (map[next] == '.' &&
                    used[next] == 0)
                {
                    used[next] = 1;
                    queue[rear++] = next;
                }
            }

            /*
            왼쪽
            */
            if (x > 0)
            {
                int next = current - 1;

                if (map[next] == '.' &&
                    used[next] == 0)
                {
                    used[next] = 1;
                    queue[rear++] = next;
                }
            }

            /*
            오른쪽
            */
            if (x + 1 < C)
            {
                int next = current + 1;

                if (map[next] == '.' &&
                    used[next] == 0)
                {
                    used[next] = 1;
                    queue[rear++] = next;
                }
            }
        }

        /*
        다음 BFS 거리
        */
        remain++;
    }

    return -1;
}

int main(void)
{
    // freopen("data.txt", "r", stdin);
    scanf("%d %d", &R, &C);

    total_dot = 0;

    /*
    한 행씩 입력

    그런데 C가 629705처럼 매우 클 수 있으므로
    별도 line[C]를 만들지 않고
    map의 해당 위치에 바로 입력한다.
    */
    for (int y = 0; y < R; y++)
    {
        scanf("%s", &map[y * C]);

        for (int x = 0; x < C; x++)
        {
            if (map[y * C + x] == '.')
            {
                total_dot++;
            }
        }
    }

    int remain = bfs();

    if (remain == -1)
    {
        printf("0\n");
        return 0;
    }

    printf("%d\n", total_dot - remain);

    return 0;
}