/*
농장에는 1번부터 N 번까지 목초지가 있음

현재 목초지 S
E번 목초지 최소시간

N 목초지의 개수 M 길의 개수


*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 100001
typedef struct Node
{
    int vertex;
    struct Node *next_node;
} Node;

int arr[MAX];
int used[MAX];
int queue[MAX];
Node *graph[MAX];

void bfs(int start)
{
    int front = 0;
    int rear = 0;
    queue[rear++] = start;
    used[start] = 1;
    arr[start] = 0;
    while (front < rear)
    {
        int current = queue[front++];

        Node *p = graph[current];

        while (p != NULL)
        {
            int next = p->vertex;
            if (used[next] == 0)
            {
                used[next] = 1;
                arr[next] = arr[current] + 1;
                queue[rear++] = next;
            }
            p = p->next_node;
        }
    }
}
void add(int a, int b)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->vertex = b;
    new_node->next_node = graph[a];
    graph[a] = new_node;
}
int main(void)
{
    freopen("data.txt", "r", stdin);
    int n, m;
    int s, e;
    scanf("%d %d", &n, &m);
    scanf("%d %d", &s, &e);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        add(a, b);
        add(b, a);
    }

    bfs(s);

    if (used[e] == 0)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n", arr[e]);
    }
    return 0;
}