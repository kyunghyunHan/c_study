/*
1. 1번을 방문 표시
2. 1번을 queue에 넣음
3. queue가 빌 때까지
   → 하나 꺼냄
   → 연결된 정점 탐색
   → 아직 방문 안 했으면?
      used 처리 + queue 삽입
4. 방문한 정점 개수 출력
*/
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


7 6
1 2
1 5
2 3
5 2
5 6
4 7
*/
int queue[MAX];
int front, rear;
int arr[MAX][MAX] = {0};
int used[MAX] = {0};
int V;
int main(void)
{
    int n = 7;
    front = 0;
    rear = 0;

    used[1] = 1;
    queue[rear++] = 1;

    int a, b;

    for (int i = 0; i < 6; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        arr[a][b] = 1;
    }
    for (int i = 1; i <= 7; i++)
    {
        for (int j = 1; j <= 7; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    while (front != rear)
    {
        int current = queue[front++];

        for (int i = 1; i <= 7; i++)
        {
            if (arr[current][i] == 1 && used[i] == 0)
            {

                used[i] = 1;
            }
        }
    }

    return 0;
};
