#include <stdio.h>
#include <stdlib.h>

/*
비숍

(row + col) % 2 색깔 구별
*/
int answer[2];
#define MAX (11)
int n;

int drr1[MAX * 2]; // \ 대각선
int drr2[MAX * 2]; // / 대각선
int arr[MAX][MAX];
int rrr1[MAX * 2];
int used[MAX][MAX];

int answer[2];

void dfs(int row, int col, int cnt, int color)
{
    if (col > n)
    {
        row++;
        col = 1;
    }

    if (row > n)
    {
        if (cnt > answer[color])
        {
            answer[color] = cnt;
        }
        return;
    }

    // 다른 색이면 그냥 통과
    if ((row + col) % 2 != color)
    {
        dfs(row, col + 1, cnt, color);
        return;
    }

    // 놓을 수 있으면 놓아본다.
    if (arr[row][col] == 1 &&
        drr1[row - col + n] == 0 &&
        drr2[row + col] == 0)
    {
        drr1[row - col + n] = 1;
        drr2[row + col] = 1;

        dfs(row, col + 1, cnt + 1, color);

        // 백트래킹
        drr1[row - col + n] = 0;
        drr2[row + col] = 0;
    }

    // 안 놓는 경우
    dfs(row, col + 1, cnt, color);
}
int main(void)
{

    // freopen("jungol.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    dfs(1, 1, 0, 0); // 한 색
    dfs(1, 1, 0, 1); // 다른 색
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= n; j++)
    //     {
    //         printf("%d", arr[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("%d\n", answer[0] + answer[1]);
    return 0;
}