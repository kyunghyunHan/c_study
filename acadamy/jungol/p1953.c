/*
미로탐색(초)


*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int used[MAX_N + 1];
int **map;
int n, m;
void dfs(int i)
{
    used[i] = 1;
    printf("%d ", i);

    int *current = map[i];
    int index = 1;
    while (index <= current[0])
    {
        int next = current[index];

        if (!used[next])
        {
            dfs(next);
        }

        index++;
    }
}
int com(const void *a, const void *b)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;

    return (ia > ib) - (ia < ib);
}
void add(int a, int b)
{
    int count = map[a][0];
    int *temp = realloc(
        map[a],
        sizeof(int) * (count + 2));
    if (temp == NULL)
    {
        exit(EXIT_FAILURE);
    }
    map[a] = temp;
    map[a][0]++;
    map[a][map[a][0]] = b;
}
int main(void)
{
    freopen("data.txt", "r", stdin);
    scanf("%d %d", &n, &m);

    map = calloc(n + 1, sizeof(*map));
    // 먼저 공간할당
    for (int i = 1; i <= n; i++)
    {

        map[i] = calloc(1, sizeof(*map[i]));
        if (map[i] == NULL)
        {
            return 1;
        }
    }

    for (int i = 1; i <= m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        add(a, b);
        add(b, a);
    }

    for (int i = 1; i <= n; i++)
    {
        qsort(
            map[i] + 1,
            map[i][0],
            sizeof(int),
            com);
    }

    dfs(1);

    for (int i = 1; i <= n; ++i)
    {
        free(map[i]);
    }

    free(map);
    return 0;
}