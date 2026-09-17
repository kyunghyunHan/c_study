#include <stdlib.h>
#include <stdio.h>

#define MAX 101

// 인접 리스트에 저장할 노드
typedef struct Node
{
    int vertex;        // 연결된 정점 번호
    struct Node *next; // 다음 인접 정점
} Node;

// BFS에서 사용할 배열 기반 큐
int queue[MAX];
int front, rear; // 꺼낼 위치와 넣을 위치

// 각 정점의 방문 여부를 저장하는 배열
int used[MAX] = {0};

// graph[i]는 i번 정점의 인접 리스트 시작 주소
Node *graph[MAX] = {NULL};

int main(void)
{
    // 큐를 빈 상태로 초기화
    front = 0;
    rear = 0;

    int a, b;

    // 간선 6개를 입력받아 인접 리스트 생성
    for (int i = 0; i < 6; i++)
    {
        scanf("%d %d", &a, &b);

        // a에서 b로 연결되는 새 노드 생성
        Node *new_node = malloc(sizeof(Node));

        new_node->vertex = b;

        // 새 노드를 a의 인접 리스트 맨 앞에 삽입
        new_node->next = graph[a];
        graph[a] = new_node;
    }

    // 1번에서 BFS 시작
    used[1] = 1;       // 큐에 넣을 때 방문 처리
    queue[rear++] = 1; // 시작 정점을 큐에 삽입

    // 큐가 빌 때까지 반복
    while (front != rear)
    {
        // 큐의 맨 앞 정점을 꺼냄
        int current = queue[front++];

        printf("%d 방문\n", current);

        // 현재 정점과 연결된 정점들을 순회
        Node *temp = graph[current];

        while (temp != NULL)
        {
            int next = temp->vertex;

            // 아직 방문하지 않은 정점만 큐에 삽입
            if (used[next] == 0)
            {
                used[next] = 1;
                queue[rear++] = next;
            }

            // 다음 인접 노드로 이동
            temp = temp->next;
        }
    }

    return 0;
}
