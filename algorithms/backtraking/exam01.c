#include <stdio.h>
int arr[2] = {0};
/*백트레킹 */
void test01(int l)
{
    if (l == 2)
    {
        printf("%d %d\n", arr[0], arr[1]);
        return;
    }

    for (int i = 1; i <= 3; i++)
    {
        arr[l] = i;
        test01(l + 1);
    }
}
/*
아래 3×3 미로에서
(0,0)에서 시작해서
(2,2)까지 가는 모든 경로를 출력해봐.
 */
int map[3][3] = {
    {0, 0, 1},
    {1, 0, 0},
    {0, 0, 0}};

int visited[3][3] = {0};

#include <stdio.h>

// 상, 하, 좌, 우
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

void dfs(int y, int x)
{
    // 목적지 도착
    if (y == 2 && x == 2)
    {
        printf("도착\n");
        return;
    }

    // 현재 위치 방문
    visited[y][x] = 1;

    // 상하 좌우 한번씩 시도
    for (int i = 0; i < 4; i++)
    {

        // 현재 위치에서 다음에 이동할 좌표 계산
        int ny = y + dy[i];
        int nx = x + dx[i];

        // 맵 밖이면 이동 불가능
        if (ny < 0 || ny >= 3 || nx < 0 || nx >= 3)
            continue;

        // 벽이면 이동 불가능
        if (map[ny][nx] == 1)
            continue;

        // 이미 방문한 곳이면 이동 불가능
        if (visited[ny][nx] == 1)
            continue;
          
        dfs(ny, nx);
    }

    // ★ 백트래킹
    visited[y][x] = 0;
}

int main(void)
{
    dfs(0, 0);

    return 0;
}
