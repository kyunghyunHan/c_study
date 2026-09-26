#include <stdio.h>
#include <stdlib.h>
int n, m;
#define MAX 6
int arr[MAX];
int used[MAX];
/*0부터 시작해 */
void dfs(int l)
{
    // 만약에 l이 3과 같다면 프린트해

    if (l == m)
    {
        for (int i = 0; i < m; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return;
    }
    // 1부터 시작해서 2로 넘어감
    for (int i = 1; i <= n; i++)
    {
        // if (used[i] == 1)
        // {
        //     continue;
        // }
        // 1은 사용햇고
        // arr에 1은 1로
        // 2러해
        used[i] = 1;
        arr[l] = i;

        dfs(l + 1);
        used[i] = 0;
    }
}
int main(void)
{
    freopen("data.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    dfs(0);
    return 0;
}
