/* 단지번호 붙이기 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 26

typedef struct
{
    int r;
    int c;
} Point;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

Point queue[MAX * MAX];

int used[MAX][MAX] = {0};
int arr[MAX][MAX] = {0};

int n;
int rear;
int front;
int count = 0;

// int danji_bfs(int sr, int sc, int vno)
// {

//     Node *stack[MAX * MAX] = {0};
// }
void input_data(void)
{
    char temp[MAX] = {0};

    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
    {
        scanf("%s", temp + 1);

        for (int j = 1; j <= n; j++)
        {
            arr[i][j] = temp[j] - '0';
        }
    }
}
void dfs(int y, int x, int n)
{
    used[y][x] = 1;
    count++;
    // while (front < rear)
    // {
    // 큐에서 하나 끄내서
    // Point current = queue[front++];

    /* 상하좌우 확인 */
    for (int d = 0; d < 4; d++)
    {

        int nr = y + dr[d];
        int nc = x + dc[d];
        /* 지도 밖이면 건너뜀 */
        if (nr < 1 || nr > n ||
            nc < 1 || nc > n)
        {
            continue;
        }

        /*
         * 1이고 아직 방문안햇다면
         방문 체크
         큐에 삽입
         * 아직 방문하지 않았다면
         */
        if (arr[nr][nc] == 1 &&
            used[nr][nc] == 0)
        {
            used[nr][nc] = 1;
            dfs(nr, nc, n);
            // queue[rear].r = nr;
            // queue[rear].c = nc;
            // rear++;
        }
    }
    // }
}
int main(void)
{
    int ans[MAX * MAX] = {0};
    //
    int house_count = 0;

    input_data();

    /* 전체 지도 탐색 */
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // 탐색 시작 ,걸리면 시작
            if (arr[i][j] == 1 && used[i][j] == 0)
            {
                front = 0;
                rear = 0;

                count = 0;
                // 방문
                used[i][j] = 1;
                // 큐에 삽입
                queue[rear].r = i;
                queue[rear].c = j;
                rear++;

                dfs(i, j, n);
                //
                // while (front < rear)
                // {
                //     // 큐에서 하나 끄내서
                //     Point current = queue[front++];

                //     /* 상하좌우 확인 */
                //     for (int d = 0; d < 4; d++)
                //     {

                //         int nr = current.r + dr[d];
                //         int nc = current.c + dc[d];

                //         /* 지도 밖이면 건너뜀 */
                //         if (nr < 1 || nr > n ||
                //             nc < 1 || nc > n)
                //         {
                //             continue;
                //         }

                //         /*
                //          * 1이고 아직 방문안햇다면
                //          방문 체크
                //          큐에 삽입
                //          * 아직 방문하지 않았다면
                //          */
                //         if (arr[nr][nc] == 1 &&
                //             used[nr][nc] == 0)
                //         {
                //             used[nr][nc] = 1;

                //             queue[rear].r = nr;
                //             queue[rear].c = nc;
                //             rear++;
                //             count++;
                //         }
                //     }
                // }

                ans[house_count] = count;
                house_count++;
            }
        }
    }

    /* 단지별 집 개수 오름차순 정렬 */
    for (int i = 0; i < house_count - 1; i++)
    {
        for (int j = i + 1; j < house_count; j++)
        {
            if (ans[i] > ans[j])
            {
                int temp = ans[i];
                ans[i] = ans[j];
                ans[j] = temp;
            }
        }
    }

    /* 단지 개수 출력 */
    printf("%d\n", house_count);

    /* 단지별 집 개수 출력 */
    for (int i = 0; i < house_count; i++)
    {
        printf("%d\n", ans[i]);
    }

    return 0;
}