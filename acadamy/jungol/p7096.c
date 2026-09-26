/*
고양이 구하기

for (int i = 0; i < 연결개수; i++)
{
    int next = graph[current][i];

    if (!used[next])
        dfs(next);       // ★ 여기서 끝까지 갔다가 돌아옴
}
*/

#include <stdio.h>
#include <stdlib.h>
int k;
int arr[101] = {0};

void bfs(int k)
{
    printf("%d ", k);
    if (arr[k] == 0)
    {
        return;
    }
    bfs(arr[k]);
}
int main(void)
{

    freopen("data.txt", "r", stdin);
    scanf("%d", &k);

    while (1)
    {
        int a, b;
        scanf("%d", &a);
        if (a == -1)
        {
            break;
        }
        scanf("%d", &b);
        for (int i = 1; i <= b; i++)
        {
            int c;
            scanf("%d", &c);
            arr[c] = a;
        }
    }

    bfs(k);
    return 0;
}