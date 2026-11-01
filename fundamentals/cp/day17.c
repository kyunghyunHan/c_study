#include <stdio.h>
#include <stdlib.h>

void dfs(int n, int graph[n + 1][n + 1], int visited[n + 1],
         int current, int *count)
{
    visited[current] = 1;

    for (int i = 1; i <= n; i++)
    {
        if (graph[current][i] == 1 && visited[i] == 0)
        {
            (*count)++;
            dfs(n, graph, visited, i, count);
        }
    }
}

int main(void)
{
    int n, q, a, b;
    scanf("%d", &n);
    scanf("%d", &q);

    int graph[n + 1][n + 1];
    int visited[n + 1];

    for (int i = 0; i <= n; i++)
    {
        visited[i] = 0;
        for (int j = 0; j <= n; j++)
        {
            graph[i][j] = 0;
        }
    }

    for (int i = 1; i <= q; i++)
    {
        scanf("%d %d", &a, &b);
        graph[a][b] = 1;
        graph[b][a] = 1;
    }

    int count = 0;
    dfs(n, graph, visited, 1, &count);

    printf("%d\n", count);

    return 0;
}
