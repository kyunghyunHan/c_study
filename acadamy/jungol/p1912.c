/*
미로탐색
두번쨰 줄부터 M 개의 줄에느 각 문이 연결하는 번호 입력
모든 방들은 문이연결 두 방 사이에는 최대 문 1개
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_M 500000
int visited[MAX_N];
int graph[MAX_N][MAX_M];
// void dfs(int i)
// {
//     // 방문
//     visited[i] = 1;
//     printf("%d ", i);
//     int *top = graph[i][0];
//     int *current = graph[i];

//     while (current != NULL)
//     {

//         if (!visited[current[top]])
//         {
//             dfs(current->vertex);
//         }
//         current = current->next_node;
//     }
// }
void add(int a, int b)
{

    graph[a][++graph[a][0]] = b;
}
int main(void)
{

    int n, m;
    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || n >= MAX_N || m < 0)
    {
        return 1;
    }

    for (int i = 0; i < m; i++)
    {
        int a, b;
        if (scanf("%d %d", &a, &b) != 2 ||
            a < 1 || a > n || b < 1 || b > n)
        {
            return 1;
        }
        add(a, b);
        add(b, a);
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= graph[i][0]; ++j)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    // dfs(1);
    printf("\n");
    return 0;
}
