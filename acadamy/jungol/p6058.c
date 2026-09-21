/*
N Rook2

체스는 가로세로 방향으로 어디곳이든 한번 이동가능

*/

#include <stdio.h>
#include <stdlib.h>
#define MAX (11)
char arr[MAX][MAX];
int used[MAX];
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
        if (arr[row][i] == '#')
        {
            continue;
        }
        if (used[i] == 1)
        {
            continue;
        }
        // 록을 배치하고
        used[i] = 1;
        dfs(row + 1);
        used[i] = 0;
    }
}
int main(void)
{

    scanf("%d", &n);
    // 입력
    for (int i = 0; i < n; i++)
    {
        scanf("%s", arr[i]);
    }
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