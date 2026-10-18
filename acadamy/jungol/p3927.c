/*
3927
Cow Hopscotch
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 17
char map[MAX][MAX];
int r, c;
int cnt;
int used[MAX][MAX];
void dfs(int start_r, int start_c)
{
    used[start_r][start_c] = 1;
    if (start_r == r && start_c == c)
    {
        cnt++;
        return;
    }
    for (int i = start_r + 1; i <= r; i++)
    {
        for (int j = start_c + 1; j <= c; j++)
        {

            if (used[i][j] == 1)
            {

                continue;
            }
            if (map[start_r][start_c] == map[i][j])
            {

                continue;
            }
            used[i][j] = 1;
            dfs(i, j);
            used[i][j] = 0;
        }
    }
}
int main(void)
{
    cnt = 0;
    freopen("data.txt", "r", stdin);
    scanf("%d %d", &r, &c);

    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= r; j++)
        {
            scanf(" %c", &map[i][j]);
        }
    }
    dfs(1, 1);
    printf("%d", cnt);
    return 0;
}