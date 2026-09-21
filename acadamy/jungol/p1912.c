#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int visited[MAX_N + 1];
int **graph;

void dfs(int i)
{
    visited[i] = 1;
    printf("%d ", i);

    int *current = graph[i];
    int index = 1;

    while (index <= current[0])
    {
        int next = current[index];

        if (!visited[next])
        {
            dfs(next);
        }

        index++;
    }
}

int compare(const void *a, const void *b)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;

    return (ia > ib) - (ia < ib);
}

void add(int **graph, int a, int b)
{
    // 현재 연결 개수
    int count = graph[a][0];

    // 0번 = count
    // 1 ~ count = 실제 데이터
    //
    // 새로운 데이터 1개를 추가할 공간 확보
    int *temp = realloc(
        graph[a],
        sizeof(int) * (count + 2)
    );

    if (temp == NULL)
    {
        exit(EXIT_FAILURE);
    }

    graph[a] = temp;

    // 개수 증가
    graph[a][0]++;

    // 마지막 위치에 b 추가
    graph[a][graph[a][0]] = b;
}

int main(void)
{
    int n, m;

    if (scanf("%d %d", &n, &m) != 2)
    {
        return 1;
    }

    // graph[0] ~ graph[n]
    graph = calloc((size_t)n + 1, sizeof(*graph));

    if (graph == NULL)
    {
        return 1;
    }

    // 처음에는 [0] 하나만 만든다.
    // graph[i][0] = 연결 개수
    for (int i = 1; i <= n; ++i)
    {
        graph[i] = calloc(1, sizeof(*graph[i]));

        if (graph[i] == NULL)
        {
            return 1;
        }
    }

    for (int i = 0; i < m; i++)
    {
        int a, b;

        if (scanf("%d %d", &a, &b) != 2 ||
            a < 1 || a > n ||
            b < 1 || b > n)
        {
            return 1;
        }

        add(graph, a, b);
        add(graph, b, a);
    }

    // 작은 번호부터 방문하기 위해 정렬
    for (int i = 1; i <= n; ++i)
    {
        qsort(
            graph[i] + 1,
            (size_t)graph[i][0],
            sizeof(graph[i][1]),
            compare
        );
    }

    dfs(1);

    printf("\n");

    // 메모리 해제
    for (int i = 1; i <= n; ++i)
    {
        free(graph[i]);
    }

    free(graph);

    return 0;
}