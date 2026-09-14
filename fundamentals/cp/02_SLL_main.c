#include "02_SLL.h"
#include <stdlib.h>
#if 0
#endif

#if 0

int main(void)
{
    nodeSLL head = {0};
    data_t data = {0};
    int n;
    (void)freopen("data.txt", "r", stdin);
    (void)scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        nodeSLL *new_node = NULL;
        (void)scanf("%d %d", &data.id, &data.score);
        new_node = Create_nodeSLL(&data);
        if (new_node != NULL)
        {
            Append_nodeSLL(&head, new_node);
        }
    }

    // 첛번쨰가 더미 노드여서
    Print_nodeSLL(head.next);
    return 0;
}

#endif
#if 1
int main(void)
{
    // 메모리할당받고 해지하기
    nodeSLL *head = NULL;
    head = (nodeSLL *)calloc(1, sizeof(nodeSLL));
    if (head == NULL)
    {
        return 1;
    }
    data_t data = {0};

    if (freopen("data.txt", "r", stdin) == NULL)
    {
        perror("data.txt");
        destroy_list(head);
        return 1;
    }

    while (scanf("%d %d", &data.id, &data.score) == 2)
    {
        nodeSLL *new_node = NULL;
        new_node = create_nodeSLL(&data);
        if (new_node != NULL)
        {
            append_nodeSLL(head, new_node);
        }
        else
        {
            destroy_list(head);
            return 1;
        }
    }

    print_nodeSLL(head->next);
    destroy_list(head);
    return 0;
}
#endif
