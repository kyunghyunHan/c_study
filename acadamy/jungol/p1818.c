/*
1. 1번을 방문 표시
2. 1번을 queue에 넣음
3. queue가 빌 때까지
   → 하나 꺼냄
   → 연결된 정점 탐색
   → 아직 방문 안 했으면?
      used 처리 + queue 삽입
4. 방문한 정점 개수 출력
*/
#include <stdlib.h>
#include <stdio.h>

#define SIZE(a) (sizeof(a) / sizeof(a[0]))
#define MAX (101)
/*
used는 같은 정점을 queue에 두번 넣지 않게한다
1.시작점을 큐에 삽입 방문표시
2.큐에 내용이 있는 동안 반복
3.그 정점과 연결된 방문하지 않은 정점을 찾음
연결점이 끝점


7 6
1 2
1 5
2 3
5 2
5 6
4 7
*/
int queue[MAX];
int stack[MAX];

int front, rear, top;
int arr[MAX][MAX] = {0};
int used[MAX] = {0};
int v, e;

int virus_dfs(int start)
{
    int used[MAX] = {0};
    front = rear = 0;
    top = 0;

    // queue[rear++] = start;
    stack[top++] = start;
    used[start] = 1;

    int cnt = 0;
    while (top > 0)
    {
        // int curr = queue[front++];
        int curr = stack[--top];
        for (int i = 1; i <= arr[curr][0]; i++)
        {
            int aa = arr[curr][i];
            if (used[aa] == 0)
            {

                used[aa] = 1;
                stack[top++] = aa;
                ++cnt;
            }
        }
    }
    return cnt;
}
int virus_bfs(int start)
{
    int used[MAX] = {0};
    front = rear = 0;
    queue[rear++] = start;
    used[start] = 1;
    int cnt = 0;
    while (front != rear)
    {
        int curr = queue[front++];
        for (int i = 1; i <= arr[curr][0]; i++)
        {
            int aa = arr[curr][i];
            if (used[aa] == 0)
            {
                ++cnt;
                queue[rear++] = aa;
                used[aa] = 1;
            }
        }
    }
    return cnt;
}
void print_arr(int (*arr)[MAX], int v)
{
    for (int i = 1; i <= v; i++)
    {
        for (int j = 1; j <= arr[i][0]; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
int main(void)
{
    int e, v1, v2;
    front = 0;
    rear = 0;

    used[1] = 1;
    queue[rear++] = 1;

    (void)scanf("%d %d", &v, &e);
    for (int i = 0; i < e; i++)
    {
        scanf("%d %d", &v1, &v2);
        arr[v1][++arr[v1][0]] = v2;
        arr[v2][++arr[v2][0]] = v1;
    }
    printf("%d\n", virus_dfs(1));
    // for (int i = 1; i <= 7; i++)
    // {
    //     for (int j = 1; j <= 7; j++)
    //     {
    //         printf("%d ", arr[i][j]);
    //     }
    //     printf("\n");
    // }

    // while (front != rear)
    // {
    //     int current = queue[front++];

    //     for (int i = 1; i <= 7; i++)
    //     {
    //         if (arr[current][i] == 1 && used[i] == 0)
    //         {

    //             used[i] = 1;
    //         }
    //     }
    // }

    return 0;
}
