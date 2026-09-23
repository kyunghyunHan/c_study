/*
밀크위드

X, Y   : 목초지의 너비(X), 높이(Y)
Mx, My : 밀크위드 시작 위치

'.' : 풀이 있는 칸 -> 밀크위드가 퍼질 수 있음
'*' : 바위 -> 밀크위드가 퍼질 수 없음

밀크위드는 매주 상하좌우 + 대각선 총 8방향으로 퍼진다.

주의:
문제의 좌표 (1,1)은 "왼쪽 아래"이지만
배열 map[1][1]은 입력 기준 "왼쪽 위"이다.

따라서 문제의 y좌표 My를 배열 좌표로 바꿀 때

    배열 y = Y - My + 1

로 변환해야 한다.

BFS를 이용해서 각 칸에
"몇 주 후에 밀크위드가 도착하는지"를 저장한다.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 102

int x, y;
int m1, m2;

/* BFS 큐의 앞/뒤 인덱스 */
int front, rear;

/*
map 값의 의미

-1 : 바위
 0 : 아직 밀크위드가 도착하지 않은 풀
 1 : 시작 위치
 2 : 1주 후 도착
 3 : 2주 후 도착
 ...
*/
int map[MAX][MAX];

/*
BFS에서 발견한 가장 큰 값

시작점을 1로 저장했기 때문에
실제 걸린 주 수는 time - 1
*/
int time;

/* 하나의 좌표를 저장 */
typedef struct Point
{
    int x; /* 열 */
    int y; /* 행 */
} Point;

/* 최대 X * Y개의 좌표가 들어갈 수 있음 */
Point queue[MAX * MAX];

/*
8방향 이동

        ↖ ↑ ↗
        ←   →
        ↙ ↓ ↘

dx, dy의 같은 인덱스끼리 한 방향을 나타낸다.
*/
int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};


/*
시작 위치 (sx, sy)에서 BFS 시작

각 칸에 밀크위드가 몇 주 후에 도착하는지를 기록한다.
*/
void bfs(int sx, int sy)
{
    /*
    시작 위치 방문 처리

    1로 시작하는 이유:
    0은 "아직 방문하지 않은 풀"을 의미하기 때문
    */
    map[sy][sx] = 1;

    /* 시작 위치를 큐에 삽입 */
    queue[rear++] = (Point){sx, sy};

    /* 시작점의 저장값은 1 */
    time = 1;

    /* 큐에 처리할 좌표가 존재하는 동안 반복 */
    while (front < rear)
    {
        /* 가장 먼저 들어온 좌표를 꺼낸다. */
        Point current = queue[front++];

        /* 현재 위치에서 8방향 확인 */
        for (int i = 0; i < 8; i++)
        {
            int next_x = current.x + dx[i];
            int next_y = current.y + dy[i];

            /*
            1. 지도 범위를 벗어나면 이동 불가능

            현재 배열을 1부터 사용하고 있으므로
            x : 1 ~ X
            y : 1 ~ Y
            */
            if (next_x < 1 || next_x > x ||
                next_y < 1 || next_y > y)
            {
                continue;
            }

            /*
            2. 0인 칸만 이동 가능

            -1 : 바위
             0 : 아직 방문하지 않은 풀
            1 이상 : 이미 밀크위드가 도착한 칸

            따라서 0이 아니면 탐색하지 않는다.
            */
            if (map[next_y][next_x] != 0)
            {
                continue;
            }

            /*
            3. 현재 칸보다 1주 뒤에 다음 칸으로 퍼진다.

            예:
            현재 칸 = 1 → 다음 칸 = 2
            현재 칸 = 2 → 다음 칸 = 3
            */
            map[next_y][next_x] =
                map[current.y][current.x] + 1;

            /*
            현재까지 발견한 가장 오래 걸리는 시간을 저장한다.

            모든 풀을 덮는 데 필요한 시간은
            가장 늦게 도착하는 칸의 시간이 된다.
            */
            if (map[next_y][next_x] > time)
            {
                time = map[next_y][next_x];
            }

            /*
            새로 방문한 칸을 큐에 넣는다.

            나중에 이 위치를 기준으로
            다시 주변 8칸으로 퍼뜨린다.
            */
            queue[rear++] = (Point){next_x, next_y};
        }
    }
}


int main(void)
{
    freopen("data.txt", "r", stdin);

    /*
    X  : 가로 길이
    Y  : 세로 길이
    m1 : Mx, 시작 x좌표
    m2 : My, 시작 y좌표
    */
    scanf("%d %d %d %d", &x, &y, &m1, &m2);

    /*
    지도 입력

    입력은 위쪽 행부터 아래쪽 행 순서로 들어온다.

    '.' → 0 : 이동 가능한 풀
    '*' → -1 : 이동할 수 없는 바위
    */
    for (int i = 1; i <= y; i++)
    {
        for (int j = 1; j <= x; j++)
        {
            char c;

            /* 앞의 공백으로 개행 문자 무시 */
            scanf(" %c", &c);

            if (c == '*')
            {
                /* 바위 */
                map[i][j] = -1;
            }
            else
            {
                /* 풀 */
                map[i][j] = 0;
            }
        }
    }

    /*
    ★ 좌표 변환이 중요 ★

    문제에서는 (1,1)이 왼쪽 아래이다.

    하지만 배열의 입력은 위에서부터 저장했으므로
    문제의 My를 배열의 행 번호로 뒤집어야 한다.

    문제 좌표:
        My = 1 → 배열 y = Y
        My = 2 → 배열 y = Y-1
        ...
        My = Y → 배열 y = 1

    따라서:

        배열 y = Y - My + 1

    x좌표는 좌우 방향이 같으므로 그대로 사용한다.
    */
    bfs(m1, y - m2 + 1);

    /*
    시작점을 1로 저장했으므로 실제 주 수는 -1

    시작점         : 1 → 0주
    한 칸 퍼짐     : 2 → 1주
    두 칸 퍼짐     : 3 → 2주
    */
    printf("%d\n", time - 1);

    return 0;
}