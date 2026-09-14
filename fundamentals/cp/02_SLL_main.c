#include "02_SLL.h"

int main(void)
{
    nodeSLL head = {0};
    data_t data = {0};
    int n;
    (void)freopen("data.txt", "r", stdin);
    (void)scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        nodeSLL *newnode = NULL;
        (void)scanf("%d %d", &data.id, &data.score);
        newnode = Create_nodeSLL(&data);
        if (newnode != NULL)
        {
            Append_nodeSLL(&head, newnode);
        }
    }
    Print_nodeSLL(head.next);
    return 0;
}