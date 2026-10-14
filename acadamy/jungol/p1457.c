#include <stdio.h>

/*영영 구하기 */
#include <stdlib.h>
#define MAX (102)
int arr[MAX][MAX];
int used[MAX][MAX];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
int m, n, k;
int answer[MAX * MAX];
int index;
int count;
int com(const void *a, const void *b)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}
void dfs(int y, int x)
{

    used[y][x] = 1;
    count++;

    for (int i = 0; i < 4; i++)
    {
        int next_x = x + dc[i];
        int next_y = y + dr[i];

        if (next_x < 0 || next_x >= n || next_y < 0 || next_y >= m)
        {
            continue;
        }
        if (arr[next_y][next_x] == 1)
        {
            continue;
        }
        if (used[next_y][next_x] == 1)
        {
            continue;
        }

        dfs(next_y, next_x);
    }
}
int main(void)
{
    freopen("data.txt", "r", stdin);
    scanf("%d %d %d", &m, &n, &k);

    for (int a = 0; a < k; a++)
    {
        int fc, fr, sc, sr;
        scanf("%d %d %d %d", &fc, &fr, &sc, &sr);

        for (int row = fr; row < sr; row++)
        {
            for (int col = fc; col < sc; col++)
            {
                arr[row][col] = 1;
            }
        }
    }
    for (int row = m - 1; row >= 0; row--)
    {
        for (int col = 0; col < n; col++)
        {
            if (used[row][col] == 0 && arr[row][col] == 0)
            {
                count = 0;
                dfs(row, col);
                answer[index++] = count;
            }
        }
    }
    printf("%d\n", index);
    qsort(answer, index, sizeof(int), com);
    for (int i = 0; i < index; i++)
    {
        printf("%d ", answer[i]);
    }
    // for (int row = m - 1; row >= 0; row--)
    // {
    //     for (int col = 0; col < n; col++)
    //     {
    //         printf("%d ", arr[row][col]);
    //     }
    //     printf("\n");
    // }
    return 0;
}