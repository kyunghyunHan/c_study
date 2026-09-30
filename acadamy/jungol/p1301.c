/*소풍 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int k, n, m;
#define MAX 1002
int queue[MAX];
int used[MAX];
int parr[MAX];
int sarr[MAX];
int arr[MAX][MAX];
int front, rear;
int cnt;
void bfs(int start)
{
    front = rear = 0;

    used[start] = 1;
    parr[start]++;
    queue[rear++] = start;

    while (front < rear)
    {
        int current = queue[front++];

        for (int i = 1; i <= arr[current][0]; i++)
        {
            int next = arr[current][i];
            if (used[next] == 1)
            {
                continue;
            }
            used[next] = 1;
            parr[next]++;
            queue[rear++] = next;
        }
    }
}
int main(void)
{
    front = 0;
    rear = 0;
    cnt = 0;
    freopen("data.txt", "r", stdin);
    // k마리의병아리
    // N개의번호가진마을
    // M개의단방향길
    scanf("%d %d %d", &k, &n, &m);

    for (int i = 0; i < k; i++)
    {
        scanf("%d", &sarr[i]);
    }
    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        arr[a][0] += 1;
        // arr[b][0] += 1;
        arr[a][arr[a][0]] = b;
        // arr[b][arr[b][0]] = a;
    }

    for (int i = 0; i < k; i++)
    {
        memset(used, 0, sizeof(used));
        bfs(sarr[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        if (parr[i] == k)
        {
            cnt++;
        }
    }
    printf("%d", cnt);
    return 0;
}