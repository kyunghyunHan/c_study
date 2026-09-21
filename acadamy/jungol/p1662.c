#include <stdio.h>
#include <stdlib.h>

/*
비숍


*/

#define MAX (11)
int n;
int answer;
int drr1[MAX * 2]; // \ 대각선
int drr2[MAX * 2]; // / 대각선
int arr[MAX][MAX];

void dfs(int row)
{
    answer++;

    for (int i = 1; i <= n; i++)
    {

        if (arr[row][i] == 0)
        {
            continue;
        }
        if (drr1[row + i - n] == 1)
        {
            continue;
        }
        if (drr2[row + i] == 1)
        {
            continue;
        }

        drr1[row + i - n] = 1;
        drr2[row + i] = 1;
        arr[row][i] = 0;
        dfs(row + 1);
        drr1[row + i - n] = 0;
        drr2[row + i] = 0;
    }
}
int main(void)
{

    freopen("jungol.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    dfs(1);
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 1; j <= n; j++)
    //     {
    //         printf("%d", arr[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("%d", answer);
    return 0;
}