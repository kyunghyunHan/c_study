#include <stdlib.h>
#include <stdio.h>

#define SIZE(a) (sizeof(a) / sizeof(a[0]))
#define MAX (101)
/*
used는 같은 정점을 queue에 두번 넣지 않게한다
1.시작점을 큐에 삽입 방문표시
2.큐에 내용이 있는 동안 반복
3.그 정점과 연결된 방문하지 않은 정점을 찾음
연결점이 끝점

*/
int queue[MAX];
int front, rear;
int arr[MAX][MAX] = {0};
int used[MAX] = {0};
int V;
int virus_bfs(int start)
{
    int used[MAX] = {0};
    front = rear = 0;
    queue[rear++] = start;
    used[start] = 1;
    int cnt = 0;
    while (front != rear)
    {
        int curr = queue[front++];
        for (int i = 1; i <= V; i++)
        {
            if (arr[curr][i] == 1 && used[i] == 0)
            {
                ++cnt;
                queue[rear++] = i;
                used[i] = 1;
            }
        }
    }
    return cnt;
}
void print_arr(int (*arr)[MAX], int v)
{
    for (int i = 1; i <= v; i++)
    {
        for (int j = 1; j <= v; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{

    int E, v1, v2;

    scanf("%d %d", &V, &E);

    for (int i = 0; i < E; i++)
    {
        scanf("%d %d", &v1, &v2);
        arr[v1][v2] = 1;
        arr[v2][v1] = 1;
    }

    printf("%d\n", virus_bfs(1));
    return 0;
}
