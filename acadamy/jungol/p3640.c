/*
잡기놀이

도훈이는 현재 0<N<100000에 취치
재우는 현재 0<N<100000에 취치

도훈이는 걷거나 점프 이동할수있음
재우는 점 k 에서 움직이지 않음
도훈이의 위치가 x일때 걷는다면 1초후에 x-1또는 x+1로 이동
점파하는걍우에 2*x이동

도훈이와 재우의 위치가 주어졋을때 도훈이가 재우를 잡는 가장 빠른시간
*/

#include <stdio.h>
#include <stdlib.h>
int n, k;
int rear, front;
#define MAX 100002
int arr[MAX];
int used[MAX];
int queue[MAX];
int answer;
void bfs(int start)
{

    rear = 0;
    front = 0;
    used[start] = 1;
    queue[rear++] = 5;
    int cnt = 0;
    while (front < rear)
    {
        int current = queue[front++];

        if (current == k)
        {
            answer = cnt;
            return;
        }
        for (int i = 0; i < 3; i++)
        {
            int next;
            if (i == 0)
            {
                next = current - 1;
            }
            else if (i == 1)
            {
                next = current + 1;
            }
            else
            {
                next = 2 * current;
            }
            if (next < 1 || next > n)
            {
                continue;
            }
            if (used[next] == 0)
            {
                continue;
            }
            used[next] = 1;
            queue[rear++] = next;
            cnt++;
        }
    }
}
int main(void)
{
    freopen("data.txt", "r", stdin);
    scanf("%d %d", &n, &k);
    bfs(n);
    printf("%d", answer);
    return 0;
}