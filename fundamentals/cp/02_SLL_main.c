#include "02_SLL.h"

#include <stdio.h>

int main(void)
{
    NodeSLL *head = NULL;
    data_t data = {0};
    int n;
    (void)freopen("data.txt", "r", stdin);
    (void)scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        NodeSLL *new_node = NULL;
        (void)scanf("%d %d", &data.id, &data.score);
        head = sll_create_node(&data);
        if (new_node != NULL)
        {
            sll_append_node(&head, new_node);
        }
        printf("%d %d\n", head->data.id, head->data.score);
    }
    // if (!sll_push_back(&head, 10) ||
    //     !sll_push_back(&head, 20) ||
    //     !sll_push_back(&head, 30) ||
    //     !sll_push_front(&head, 5))
    // {
    //     fputs("메모리 할당에 실패했습니다.\n", stderr);
    //     sll_clear(&head);
    //     return 1;
    // }

    // printf("리스트: ");
    // sll_print(head);
    // printf("노드 수: %zu\n", sll_length(head));

    // if (sll_find(head, 20) != NULL)
    // {
    //     puts("20을 찾았습니다.");
    // }

    // if (sll_remove(&head, 20))
    // {
    //     printf("20 삭제 후: ");
    //     sll_print(head);
    // }

    // sll_clear(&head);
    return 0;
}
