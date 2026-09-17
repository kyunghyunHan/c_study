/*1번부투 N번까지


*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, e;
    int start;
    int rear, front;
    int queue[7 * 7];
    int used[7] = {0};
    scanf("%d %d", &n, &e);
    int arr[7][7] = {0};
    for (int i = 0; i < e; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        arr[a][b] = 1;
        arr[b][a] = 1; // 양방향
    }
    scanf("%d", &start);

    rear = 0;
    front = 0;
    queue[rear++] = start;
    used[start] = 1;

    while (front < rear)
    {
        int current = queue[front];
        front += 1;
        for (int i = 1; i <= n; i++)
        {
            if (arr[current][i] == 1 && used[i] == 0)
            {

                queue[rear++] = i;
                used[i] = 1;
            }
        }
    }
    // for (int i = 1; i <= e; i++)
    // {
    //     for (int j = 1; j <= e; j++)
    //     {
    //         printf("%d ", arr[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("%d\n", rear);

    return 0;
}