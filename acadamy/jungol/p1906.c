/*
촌수 계산

n: 전체 사람의 수
촌수를 계산해야 하는 서로 다른 사람의 번호
m: 관계의 수

x: y의 부모

*/
#include <stdio.h>
#include <stdlib.h>
int graph[101][101];
int used[101];
int cnt = 0;
int current, target;
int answer;
void dfs(int current, int cnt)
{
    if (current == target)
    {
        answer = cnt;
        return;
    }
    used[current] = 1;

    for (int i = 1; i <= graph[current][0]; i++)
    {
        int next = graph[current][i];
        if (used[next] == 1)
            continue;

        dfs(next, cnt + 1);
    }
}
int main(void)
{
    // freopen("data.txt", "r", stdin);

    int n;
    int m;

    scanf("%d", &n);
    scanf("%d %d", &current, &target);
    scanf("%d", &m);

    for (int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x][++graph[x][0]] = y;
        graph[y][++graph[y][0]] = x;
    }
    dfs(current, 0);
    if (answer == 0)
    {
        printf("%d", -1);
        return 0;
    }
    printf("%d", answer);
    return 0;
}