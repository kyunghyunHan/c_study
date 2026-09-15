#include "02_cll.h"

void init(Node **head)
{
    *head = (Node *)calloc(1, sizeof(Node));
    if (*head == NULL)
    {
        return;
    }
    (**head).next = *head;
    (**head).prev = *head;
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
void cdll_append_node(Node *head, Node *new_node)
{
    if (head == NULL || new_node == NULL)
    {
        return;
    }

    Node *tail = head->prev;

    tail->next = new_node;
    new_node->prev = tail;

    new_node->next = head;
    head->prev = new_node;
}