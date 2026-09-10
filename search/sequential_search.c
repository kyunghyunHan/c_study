#include "../struct/linked_list.h"
/*
gcc -Wall -Wextra \
  ./search/sequential_search.c \
  ./struct/linked_list.c \
  -o test && ./test
*/

#include <stdio.h>

Node *sll_sequential_search(Node *head, int target)
{
    Node *current = head;

    while (current != NULL)
    {
        if (current->data == target)
            return current;

        current = current->next_node;
    }

    return NULL;
}

Node *sll_move_to_front(Node **head, int target)
{
    Node *current = *head;
    Node *previous = NULL;

    while (current != NULL)
    {
        if (current->data == target)
        {
            if (previous != NULL)
            {
                previous->next_node = current->next_node;
                current->next_node = *head;
                *head = current;
            }
            return current;
        }

        previous = current;
        current = current->next_node;
    }

    return NULL;
}

Node *sll_transpose(Node **head, int target)
{
    Node *current = *head;
    Node *previous_previous = NULL;
    Node *previous = NULL;

    while (current != NULL)
    {
        if (current->data == target)
        {
            if (previous != NULL)
            {
                if (previous_previous != NULL)
                    previous_previous->next_node = current;
                else
                    *head = current;

                previous->next_node = current->next_node;
                current->next_node = previous;
            }
            return current;
        }

        previous_previous = previous;
        previous = current;
        current = current->next_node;
    }

    return NULL;
}

int main(void)
{
    int i;
    int init_value[10] = {1, 2, 6, 10, 4, 9, 5, 3, 8, 7};
    Node *list = NULL;
    Node *current;
    Node *new_node;
    Node *match;

    for (i = 0; i < 10; i++)
    {
        new_node = sll_create_node(init_value[i]);
        sll_append_node(&list, new_node);
    }

    printf("Simple Sequential Search...\n");
    match = sll_sequential_search(list, 9);
    if (match != NULL)
        printf("Found : %d\n", match->data);
    else
        printf("Not Found : 9\n");

    printf("Move To Front...\n");
    match = sll_move_to_front(&list, 4);
    if (match != NULL)
        printf("Found : %d\n", match->data);
    else
        printf("Not Found : 4\n");

    printf("Transpose...\n");
    match = sll_transpose(&list, 7);
    if (match != NULL)
        printf("Found : %d\n", match->data);
    else
        printf("Not Found : 7\n");

    printf("Destroying List...\n");
    while (list != NULL)
    {
        current = list;
        sll_remove_node(&list, current);
        sll_destroy_node(current);
    }

    return 0;
}
