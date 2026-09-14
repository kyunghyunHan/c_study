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

void append_node(Node **head, Node *new_node)
{
    if (head == NULL || new_node == NULL)
    {
        return;
    }
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        Node *tail = *head;
        while (tail->next_node != NULL)
        {
            tail = tail->next_node;
        }
        //새로운 노드의 이전 노드는 테일이 가리키고 있던 이전 노드
        new_node->prev_node = tail->prev_node;
        //새로온 노드의 다음 노드는 테일
        new_node->next_node = tail;
        //테일의 이전노드의 다음노드는 새로운 노드 가리키게
        tail->prev_node->next_node = new_node;
        //테일의 이전 노드는 새로운 노드가 댐
        tail->prev_node = new_node;
    }
}

void print_node(Node *head)
{
    if (head != NULL)
    {
        head = head->next_node;
    }

    for (; head != NULL && head->next_node != NULL;
         head = head->next_node)
    {
        printf("%d %d\n", head->data.id, head->data.score);
    }
}
