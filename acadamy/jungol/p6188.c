#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int val;
    struct Node *next;
} Node;
Node *graph[50002];
int used[50002];
int n, m;
void dfs(int start)
{
    used[start] = 1;

    Node *current = graph[start];

    while (current != NULL)
    {
        int next = current->val;
        if (used[next] == 0)
        {
            dfs(next);
        }
        current = current->next;
    }
}
void add(int a, int b)
{
    Node *new_node = malloc(sizeof(Node));

    new_node->val = b;
    new_node->next = graph[a];
    graph[a] = new_node;
}
int main(void)
{
    // freopen("data.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        add(a, b);
        add(b, a);
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (used[i] == 0)
        {
            dfs(i);
            cnt++;
        }
    }
    printf("%d", cnt);
    return 0;
}