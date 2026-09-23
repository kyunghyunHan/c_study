/*
화염에서 탈출

. : 빈칸
* : 불
X : 바위
D : 목적지
S : 재우

핵심:
1. 사람을 현재 레벨만큼 이동
2. 불을 현재 레벨만큼 확산
3. 다음 시간으로 넘어감

사람이 이동한 위치에 같은 시간에 불이 들어올 수도 있으므로
다음에 person_queue에서 꺼낼 때 그 위치가 불인지 확인한다.
*/

#include <stdio.h>

#define MAX 52

typedef struct
{
    int r;
    int c;
} Point;

/*
arr
 0 : 빈칸
 1 : 바위
 2 : 목적지 D
-1 : 불
*/
int arr[MAX][MAX];

/* 사람 방문 체크 */
int used[MAX][MAX];

/* 불 큐 */
Point fire_queue[MAX * MAX];
int f_front;
int f_rear;

/* 사람 큐 */
Point person_queue[MAX * MAX];
int p_front;
int p_rear;

/* 상하좌우 */
int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};

int r, c;

int bfs(void)
{
    int time = 0;

    /* 사람이 이동할 곳이 남아있는 동안 */
    while (p_front < p_rear)
    {
        /*
        ====================================
        1. 사람을 이번 시간만큼 이동
        ====================================
        */

        /*
        지금 큐에 있는 사람 위치 개수만 저장.

        BFS 도중 새롭게 추가되는 위치는
        다음 시간에 처리해야 한다.
        */
        int person_count = p_rear - p_front;

        /* 이제 1분 후 위치로 이동 */
        time++;

        for (int i = 0; i < person_count; i++)
        {
            Point current = person_queue[p_front++];

            /*
            이전 시간에 이 위치까지 불이 들어왔다면
            이 경로의 사람은 죽었으므로 이동 불가능
            */
            if (arr[current.r][current.c] == -1)
            {
                continue;
            }

            for (int d = 0; d < 4; d++)
            {
                int next_r = current.r + dy[d];
                int next_c = current.c + dx[d];

                /* 범위 체크 */
                if (next_r < 1 || next_r > r ||
                    next_c < 1 || next_c > c)
                {
                    continue;
                }

                /*
                목적지 발견

                현재 time분째 이동 중이므로
                바로 time 반환
                */
                if (arr[next_r][next_c] == 2)
                {
                    return time;
                }

                /*
                빈칸이 아니면 이동 불가능

                1  : 바위
                -1 : 불
                */
                if (arr[next_r][next_c] != 0)
                {
                    continue;
                }

                /* 이미 사람이 방문한 곳 */
                if (used[next_r][next_c] == 1)
                {
                    continue;
                }

                /* 방문 처리 */
                used[next_r][next_c] = 1;

                /* 다음 시간에 처리 */
                person_queue[p_rear++] =
                    (Point){next_r, next_c};
            }
        }

        /*
        ====================================
        2. 불을 이번 시간만큼 확산
        ====================================
        */

        /*
        현재 존재하는 불의 개수만 처리.

        여기서 새로 생기는 불은
        다음 시간에 처리한다.
        */
        int fire_count = f_rear - f_front;

        for (int i = 0; i < fire_count; i++)
        {
            Point current = fire_queue[f_front++];

            for (int d = 0; d < 4; d++)
            {
                int next_r = current.r + dy[d];
                int next_c = current.c + dx[d];

                /* 범위 체크 */
                if (next_r < 1 || next_r > r ||
                    next_c < 1 || next_c > c)
                {
                    continue;
                }

                /*
                불은 빈칸으로만 확산

                바위 X → 못 감
                집 D   → 못 감
                기존 불 → 다시 갈 필요 없음
                */
                if (arr[next_r][next_c] != 0)
                {
                    continue;
                }

                /* 불로 변경 */
                arr[next_r][next_c] = -1;

                /* 다음 시간에 처리할 불 */
                fire_queue[f_rear++] =
                    (Point){next_r, next_c};
            }
        }
    }

    /* 사람 큐가 비었는데 목적지에 도착 못함 */
    return -1;
}

int main(void)
{
    // freopen("jungol.txt", "r", stdin);

    scanf("%d %d", &r, &c);

    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            char temp;

            /* 앞의 공백으로 개행문자 무시 */
            scanf(" %c", &temp);

            if (temp == '.')
            {
                /* 빈칸 */
                arr[i][j] = 0;
            }
            else if (temp == 'X')
            {
                /* 바위 */
                arr[i][j] = 1;
            }
            else if (temp == 'D')
            {
                /* 목적지 */
                arr[i][j] = 2;
            }
            else if (temp == '*')
            {
                /* 불 */
                arr[i][j] = -1;

                /*
                처음 존재하는 모든 불을 큐에 넣음
                → 다중 시작점
                */
                fire_queue[f_rear++] =
                    (Point){i, j};
            }
            else if (temp == 'S')
            {
                /*
                S가 있던 위치는 빈칸으로 처리.

                사람이 이동한 후
                불이 이 위치로 들어올 수 있어야 한다.
                */
                arr[i][j] = 0;

                /* 사람 시작점 */
                person_queue[p_rear++] =
                    (Point){i, j};

                /* 시작점 방문 */
                used[i][j] = 1;
            }
        }
    }

    int result = bfs();

    if (result == -1)
    {
        printf("impossible\n");
    }
    else
    {
        printf("%d\n", result);
    }

    return 0;
}