#include "02_cll.h"

void init(Node **head, Node **tail)
{
    *head = (Node *)calloc(1, sizeof(Node));
    if (*head == NULL)
    {
        return;
    }
    *tail = (Node *)calloc(1, sizeof(Node));
    if (*tail == NULL)
    {
        free(*head);
        *head = NULL;

        return;
    }
    (**head).next = *tail;
    (**tail).prev = *head;
}

Node *create_node(data_t new_data)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        return NULL;
    }

    new_node->data = new_data;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}