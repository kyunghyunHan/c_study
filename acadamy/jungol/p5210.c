#include <stdio.h>
#include <stdlib.h>

#define MAX 11

// arr[x][0] = x번 노드와 연결된 노드 개수
// arr[x][1...] = x번 노드와 연결된 노드 번호
int arr[MAX][MAX];

// used[x] = x번 노드에 칠한 색
// 0이면 아직 색칠 안 함
int used[MAX];

int answer = 0;

int n; // 노드 개수
int m; // 색 개수
int k; // 간선 개수

void dfs(int current)
{
    // 1번
    //  1~n번 노드까지 전부 색칠했다면
    if (current > n)
    {
        answer++;
        return;
    }
    // 먼저 색을 고름
    //  현재 노드에 1~m번 색을 하나씩 칠해본다.
    for (int color = 1; color <= m; color++)
    {
        int possible = 1;

        // current와 연결된 모든 노드 검사
        for (int i = 1; i <= arr[current][0]; i++)
        {
            int next = arr[current][i];
           
            // 연결된 노드가 현재 칠하려는 색과 같으면 불가능
            if (used[next] == color)
            {
                possible = 0;
                break;
            }
        }

        // 이 색을 사용할 수 없다면 다음 색 검사
        if (possible == 0)
        {
            continue;
        }

        // 현재 노드에 color 색 선택
        used[current] = color;

        // 다음 노드 색칠하러 이동
        dfs(current + 1);

        // 돌아왔으므로 선택 취소 (백트래킹)
        used[current] = 0;
    }
}

int main(void)
{
    freopen("data.txt", "r", stdin);
    // n = 노드 개수
    // m = 사용할 수 있는 색 개수
    scanf("%d %d", &n, &m);

    // 연결선 개수
    scanf("%d", &k);

    // 그래프 입력
    for (int i = 0; i < k; i++)
    {
        int a, b;

        scanf("%d %d", &a, &b);

        // a -> b
        arr[a][0]++;
        arr[a][arr[a][0]] = b;

        // b -> a
        arr[b][0]++;
        arr[b][arr[b][0]] = a;
    }

    // 1번 노드부터 색칠 시작
    dfs(1);

    printf("%d\n", answer);

    return 0;
}