#include <stdio.h>
#include <stdlib.h>
int n, m;
int top;
int stack[7];
int used[7];
void dfs(int l)
{
    // M개를 다 골랐다.
    if (l == m)
    {
        for (int i = 0; i < m; i++)
        {
            printf("%d ", stack[i]);
        }
        printf("\n");
        return;
    }
    // 현재 L번쨰 에 1~ n중 하나 선택
    //  현재 l번째 칸에 1~N 중 하나 선택
    for (int i = 1; i <= n; i++)
    {
        if (used[i] == 1)
            continue;

        used[i] = 1; // i 선택

        stack[l] = i;
        dfs(l + 1);

        used[i] = 0; // ★ 돌아왔으니까 선택 취소
    }
}
int main(void)
{
    // freopen("data.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    dfs(0);
    return 0;
}