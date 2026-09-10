#include "linked_list.h"

#include <stdlib.h>

Node *sll_create_node(ElementType new_data)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
        return NULL;

    new_node->data = new_data;
    new_node->next_node = NULL;
    return new_node;
}

void sll_destroy_node(Node *node)
{
    free(node);
}

void sll_append_node(Node **head, Node *new_node)
{
    Node *tail;

    if (head == NULL || new_node == NULL)
        return;

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    tail = *head;
    while (tail->next_node != NULL)
        tail = tail->next_node;

    tail->next_node = new_node;
}

Node *sll_get_node_at(Node *head, int location)
{
    Node *current = head;

    if (location < 0)
        return NULL;

    while (current != NULL && location > 0)
    {
        current = current->next_node;
        location--;
    }

    return current;
}

void sll_remove_node(Node **head, Node *remove)
{
    Node *current;

    if (head == NULL || *head == NULL || remove == NULL)
        return;

    if (*head == remove)
    {
        *head = remove->next_node;
        return;
    }

    current = *head;
    while (current != NULL && current->next_node != remove)
        current = current->next_node;

    if (current != NULL)
        current->next_node = remove->next_node;
}

void sll_insert_after(Node *current, Node *new_node)
{
    if (current == NULL || new_node == NULL)
        return;

    new_node->next_node = current->next_node;
    current->next_node = new_node;
}

void sll_insert_new_head(Node **head, Node *new_head)
{
    if (head == NULL || new_head == NULL)
        return;

    new_head->next_node = *head;
    *head = new_head;
}

int sll_get_node_count(Node *head)
{
    int count = 0;
    Node *current = head;

    while (current != NULL)
    {
        current = current->next_node;
        count++;
    }

    return count;
}
