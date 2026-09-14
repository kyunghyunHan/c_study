#include "02_dll.h"

void init_HT(Node **head, Node **tail)
{
    *head = (Node *)calloc(1, sizeof(Node));
    if (*head == NULL)
    {
        exit(0);
    }
    *tail = (Node *)calloc(1, sizeof(Node));
    if (*tail == NULL)
    {
        free(*head);
        exit(0);
    }
    (*head)->next_node = *tail;
    (*tail)->prev_node = *head;
    return;
}
Node *create_node(data_t *data)
{
    Node *newnode = NULL;
    newnode = (Node *)malloc(sizeof(Node));
    if (newnode != NULL)
    {
        newnode->data = *data;
        newnode->prev_node = NULL;
        newnode->next_node = NULL;
    }
    return newnode;
}
