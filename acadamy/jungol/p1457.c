#include <stdio.h>

/*영영 구하기 */
#include <stdlib.h>
#define MAX (102)
int arr[MAX][MAX];
int used[MAX][MAX];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
int m, n, k;
int *answer;
int index;
int count;
void dfs(int x, int y)
{

    used[x][y] = 1;
    count++;

    for (int i = 0; i < 4; i++)
    {
        int next_x = x + dc[i];
        int next_y = y + dr[i];

        if (next_x < 0 || next_x > m || next_y < 0 || next_y > n)
        {
            continue;
        }
        if (arr[next_x][next_y] == 1)
        {
            continue;
        }
        if (used[next_x][next_y] == 1)
        {
            continue;
        }
        dfs(next_x, next_y);
    }
}
int main(void)
{

    freopen("jdata.txt", "r", stdin);
    scanf("%d %d %d", &m, &n, &k);

    for (int a = 0; a < k; a++)
    {
        int fc, fr, sc, sr;
        scanf("%d %d %d %d", &fc, &fr, &sc, &sr);

        for (int i = fr; i < sr; i++)
        {
            for (int j = fc; j < sc; j++)
            {
                arr[i][j] = 1;
            }
        }
    }

    for (int row = 1; row <= m; row++)
    {
        for (int col = 1; col <= n; col++)
        {
            // 직사각형이 아니고 + 아직 방문 안 했으면
            if (arr[row][col] == 0 &&
                used[row][col] == 0)
            {
                count = 0;
                dfs(row, col);
                printf("%d\n", count);
            }
        }
    }

    return 0;
}