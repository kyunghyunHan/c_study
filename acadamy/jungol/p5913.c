/*
친구의  친구의 친구

친구의 친구까지 친구

친구의 친구의 친구까지 친구는 아님

첫번쨰 줄에 N 500
두번쨰 줄에 M 10000

1번학생의 친구의 수가 몇명인지



*/
#include <stdio.h>
#include <stdlib.h>
int graph[501][501];
int used[501];
int n, m;
int cnt;
void dfs(int start, int depth)
{
    if (depth == 2)
    {
        return;
    }
    used[start] = 1;
    for (int i = 1; i <= graph[start][0]; i++)
    {
        int next = graph[start][i];

        if (used[next] == 1)
        {
            continue;
        }
        if (used[next] == 0 || used[next] > depth + 1)
        {
            // 거리 저장
            used[next] = depth + 1;

            dfs(next, depth + 1);
        }
    }
}
int main(void)
{
    cnt = 0;
    freopen("data.txt", "r", stdin);

    scanf("%d", &n);
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][++graph[a][0]] = b;
        graph[b][++graph[b][0]] = a;
    }
    dfs(1, 0);
    for (int i = 2; i <= n; i++)
    {
        if (used[i] == 1 || used[i] == 2)
        {
            cnt++;
        }
    }
    printf("%d", cnt);
    return 0;
}