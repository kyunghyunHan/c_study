#include <stdio.h>
#include <stdlib.h>

#define N (9)

int graph[N][N] = {
    // 0  1  2  3  4  5  6  7  8
    {0, 1, 0, 0, 0, 0, 0, 0, 0}, // 0
    {1, 0, 1, 1, 0, 0, 0, 0, 0}, // 1
    {0, 1, 0, 1, 1, 0, 0, 0, 0}, // 2
    {0, 1, 1, 0, 1, 1, 0, 0, 0}, // 3
    {0, 0, 1, 1, 0, 0, 0, 0, 0}, // 4
    {0, 0, 0, 1, 0, 0, 1, 1, 0}, // 5
    {0, 0, 0, 0, 0, 1, 0, 0, 1}, // 6
    {0, 0, 0, 0, 0, 1, 0, 0, 0}, // 7
    {0, 0, 0, 0, 0, 0, 1, 0, 0}  // 8
};

int used[N] = {0};

/* =========================
   재귀 DFS
   ========================= */

void dfs(int current)
{
    used[current] = 1;

    printf("%d ", current);

    for (int i = 0; i < N; i++)
    {
        if (graph[current][i] == 1 &&
            used[i] == 0)
        {
            dfs(i);
        }
    }
}

/* =========================
   Stack DFS
   ========================= */

void dfs_stack(int start)
{
    int stack[N * N];
    int top = 0;

    stack[top++] = start;

    while (top > 0)
    {
        // pop
        int current = stack[--top];

        if (used[current] == 1)
            continue;

        used[current] = 1;

        printf("%d ", current);

        // 작은 번호부터 방문하기 위해
        // 큰 번호부터 stack에 push
        for (int i = N - 1; i >= 0; i--)
        {
            if (graph[current][i] == 1 &&
                used[i] == 0)
            {
                stack[top++] = i;
            }
        }
    }
}

int main(void)
{
    printf("recursive DFS : ");

    dfs(0);

    printf("\n");

    // used 초기화
    for (int i = 0; i < N; i++)
    {
        used[i] = 0;
    }

    printf("stack DFS     : ");

    dfs_stack(0);

    printf("\n");

    return 0;
}