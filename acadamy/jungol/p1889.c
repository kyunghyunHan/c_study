/*
N Queen


행 필요없음
체스는 가로세로댁가선 방향으로 어디곳이든 한번 이동가능


4


대각선

- +

결과 2
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX (13)
char arr[MAX][MAX];
int used[MAX];
int drr1[MAX * 2]; // \ 대각선
int drr2[MAX * 2]; // / 대각선
// int dy[4] = {1, -1, 0, 0};
// int dx[4] = {0, 0, 1, -1};
int answer = 0;
int n;
void dfs(int row)

{
    // 모든 행에 록을 하나씩 넣었으면
    if (row == n)
    {
        answer++;
        return;
    }
    for (int i = 0; i < n; i++)
    {

//0 - 1  -1+
        if (drr1[row - i + n] == 1)
        {
            continue;
        }

        // / 방향 대각선
        if (drr2[row + i] == 1)
        {
            continue;
        }

        if (used[i] == 1)
        {
            continue;
        }
        // 록을 배치하고
        used[i] = 1;
        drr1[row - i + n] = 1;
        drr2[row + i] = 1;

        dfs(row + 1);

        used[i] = 0;
        drr1[row - i + n] = 0;
        drr2[row + i] = 0;
    }
}
int main(void)
{
    // freopen("jungol.txt", "r", stdin);
    scanf("%d", &n);

    // 입력
    // for (int i = 0; i < n; i++)
    // {
    //     scanf("%s", arr[i]);
    // }
    // print
    dfs(0);
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%c", arr[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("%d", answer);
    return 0;
}