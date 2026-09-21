#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE(a) (sizeof(a) / sizeof((a)[0]))

// 인접 리스트 - 바이러스 (BFS/DFS)
#if 01

#define MAX (101)

int arr[MAX][MAX] = {0};  // 인접 리스트
int V;

void print_arr(int (*arr)[MAX], int v)
{
    printf("arr\n");

    for (int i = 1; i <= v; ++i)
    {
        for (int j = 0; j <= arr[i][0]; ++j)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

/*
BFS (Breadth-First Search, 너비 우선 탐색)

1. 시작점(start)을 큐에 삽입, 방문 표시

2. 큐에 내용이 있는 동안 반복 (front != rear)
   2-1. 큐에서 정점을 꺼냄
   2-2. 그 정점과 연결된 방문하지 않은 정점을 찾음
   2-3. 연결점을 큐에 삽입하고 방문 표시
*/
int virus_bfs(int start)
{
    int queue[MAX];
    int front, rear;
    int used[MAX] = {0};
    int cnt = 0;

    front = rear = 0;

    queue[rear++] = start;
    used[start] = 1;

    while (front != rear)
    {
        int curr = queue[front++];

        // printf("%d\n", curr);

        for (int i = 1; i <= arr[curr][0]; ++i)
        {
            int next = arr[curr][i];

            if (!used[next])
            {
                ++cnt;

                queue[rear++] = next;
                used[next] = 1;
            }
        }
    }

    return cnt;
}

/*
DFS (Depth-First Search, 깊이 우선 탐색)

1. 시작점(start)을 스택에 삽입, 방문 표시

2. 스택에 내용이 있는 동안 반복 (top > 0)
   2-1. 스택에서 정점을 꺼냄
   2-2. 그 정점과 연결된 방문하지 않은 정점을 찾음
   2-3. 연결점을 스택에 삽입하고 방문 표시
*/
int virus_dfs(int start)
{
    int stack[MAX];
    int used[MAX] = {0};
    int cnt = 0;
    int top = 0;

    stack[top++] = start;
    used[start] = 1;

    while (top > 0)
    {
        int curr = stack[--top];

        // printf("%d\n", curr);

        for (int i = 1; i <= arr[curr][0]; ++i)
        {
            int next = arr[curr][i];

            if (!used[next])
            {
                ++cnt;

                stack[top++] = next;
                used[next] = 1;
            }
        }
    }

    return cnt;
}


// 재귀 함수를 사용한 DFS 구현

int used[MAX] = {0};
int virus_cnt = 0;

void virus_recursive(int curr)
{
    for (int i = 1; i <= arr[curr][0]; ++i)
    {
        int next = arr[curr][i];

        if (!used[next])
        {
            ++virus_cnt;
            used[next] = 1;

            virus_recursive(next);
        }
    }
}

int main(void)
{
    int E, v1, v2;

    (void)freopen("06_data.txt", "r", stdin);

    (void)scanf("%d %d", &V, &E);

    for (int i = 0; i < E; ++i)
    {
        (void)scanf("%d %d", &v1, &v2);

        // 양방향 그래프이므로 양쪽 모두 저장
        arr[v1][++arr[v1][0]] = v2;
        arr[v2][++arr[v2][0]] = v1;
    }

    // print_arr(arr, V);
    // printf("%d\n", virus_dfs(1));

    used[1] = 1;
    virus_cnt = 0;

    virus_recursive(1);

    printf("%d\n", virus_cnt);

    return 0;
}

#endif


// 인접 행렬 - 바이러스
#if 0

#define MAX (101)

int arr[MAX][MAX] = {0};  // 인접 행렬

int queue[MAX];
int front, rear;
int V;

void print_arr(int (*arr)[MAX], int v)
{
    for (int i = 1; i <= v; ++i)
    {
        for (int j = 1; j <= v; ++j)
        {
            printf("%d ", arr[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

/*
BFS (Breadth-First Search, 너비 우선 탐색)

1. 시작점(start)을 큐에 삽입, 방문 표시

2. 큐에 내용이 있는 동안 반복 (front != rear)
   2-1. 큐에서 정점을 꺼냄
   2-2. 그 정점과 연결된 방문하지 않은 정점을 찾음
   2-3. 연결점을 큐에 삽입하고 방문 표시
*/
int virus_bfs(int start)
{
    int used[MAX] = {0};
    int cnt = 0;

    front = rear = 0;

    queue[rear++] = start;
    used[start] = 1;

    while (front != rear)
    {
        int curr = queue[front++];

        // printf("%d\n", curr);

        for (int i = 1; i <= V; ++i)
        {
            if (arr[curr][i] && used[i] == 0)
            {
                ++cnt;

                queue[rear++] = i;
                used[i] = 1;
            }
        }
    }

    return cnt;
}

int main(void)
{
    int E, v1, v2;

    (void)scanf("%d %d", &V, &E);

    for (int i = 0; i < E; ++i)
    {
        (void)scanf("%d %d", &v1, &v2);

        arr[v1][v2] = 1;
        arr[v2][v1] = 1;
    }

    print_arr(arr, V);

    printf("%d\n", virus_bfs(1));

    return 0;
}

#endif