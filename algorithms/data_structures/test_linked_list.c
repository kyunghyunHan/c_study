#include "linked_list.h"

#include <stdio.h>

int main(void)
{
    int i;
    int count;
    Node *list = NULL;
    Node *current;
    Node *new_node;

    for (i = 0; i < 5; i++)
    {
        new_node = sll_create_node(i);
        sll_append_node(&list, new_node);
    }

    sll_insert_new_head(&list, sll_create_node(-1));
    sll_insert_new_head(&list, sll_create_node(-2));

    count = sll_get_node_count(list);
    for (i = 0; i < count; i++)
    {
        current = sll_get_node_at(list, i);
        printf("List[%d] : %d\n", i, current->data);
    }

    printf("\nInserting 3000 After [2]...\n\n");
    current = sll_get_node_at(list, 2);
    sll_insert_after(current, sll_create_node(3000));

    count = sll_get_node_count(list);
    for (i = 0; i < count; i++)
    {
        current = sll_get_node_at(list, i);
        printf("List[%d] : %d\n", i, current->data);
    }

    printf("\nDestroying List...\n");
    while (list != NULL)
    {
        current = list;
        sll_remove_node(&list, current);
        sll_destroy_node(current);
    }

    return 0;
}
