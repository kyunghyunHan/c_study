/*
호수 찾기
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 102
int used[MAX][MAX];
int map[MAX][MAX] = {0};
int n, m, k;
void add(int r, int c)
{
    map[r][++map[r][0]] = c;
}
int main(void)
{
    freopen("data.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < k; i++)
    {
        int k1, k2;
        scanf("%d %d", &k1, &k2);
        add(k1, k2);
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            printf(" %d", map[i][j]);
        }
        printf("\n");
    }
    return 0;
}