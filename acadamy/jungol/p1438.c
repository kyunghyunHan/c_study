
#include <stdio.h>
#define MAX 101
int map[MAX][MAX];
int main(void)
{
    freopen("data.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        for (int j = y; j < y + 10; j++)

        {
            for (int k = x; k < x + 10; k++)
            {
                map[j][k] = 1;
            }
        }
    }
    int cnt = 0;
    for (int row = 0; row < MAX; row++)
    {
        for (int col = 0; col < MAX; col++)
        {
            if (map[row][col] == 1)
            {
                cnt++;
            }
        }
    }

    printf("%d", cnt);
    return 0;
}