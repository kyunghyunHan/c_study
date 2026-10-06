/*루트에서 리프까지
1번 노드가 루트노드
c 는 노드번호
d1과 d2해당 노드에 연결된 두 자식 노드
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 1002
int map[MAX][2];

int cnt;
int answer;
void bfs(int start, int cnt)
{

    if (map[start][0] == 0 && map[start][1] == 0)
    {
        // printf("this");
        if (answer < cnt)
        {
            answer = cnt;
        }

        return;
    }
    for (int i = 0; i < 2; i++)
    {

        int next = map[start][i];
        if (next == 0)
        {
            continue;
        }

        bfs(next, cnt + 1);
    }
}
int main(void)
{
    answer = 0;
    cnt = 0;
    // freopen("data.txt", "r", stdin);
    int p;
    scanf("%d", &p);
    for (int i = 0; i < p; i++)
    {
        int c, d1, d2;
        scanf("%d %d %d", &c, &d1, &d2);
        map[c][0] = d1;
        map[c][1] = d2;
    }
    bfs(1, 0);
    printf("%d", answer);
    return 0;
}