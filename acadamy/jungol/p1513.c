#include <stdio.h>

int n;
char arr[30];
int cnt = 0;
void dfs(int l, int win, int lose)
{
    // 솔아가 먼저 n승 → 우승이므로 출력
    // 3승이면 먼저 출력
    if (win == n)
    {
        for (int i = 0; i < l; i++)
        {
            printf("%c", arr[i]);
        }
        cnt++;
        printf("\n");
        return;
    }

    // 상대가 먼저 n승 → 솔아가 졌으므로 출력 X
    // 지면 출력 x
    if (lose == n)
    {
        return;
    }

    // 이번 경기를 솔아가 이긴다.
    arr[l] = 'o';
    dfs(l + 1, win + 1, lose);

    // 이번 경기를 솔아가 진다.
    arr[l] = 'x';
    dfs(l + 1, win, lose + 1);
}

int main(void)
{
    freopen("data.txt", "r", stdin);
    scanf("%d", &n);

    dfs(0, 0, 0);
    printf("total %d cases", cnt);
    return 0;
}