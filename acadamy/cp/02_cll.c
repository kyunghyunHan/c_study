#include "02_cll.h"
/*
더미 있는버전
head는 처음에는 자기 자신을 가리킨다.
head->next는 첫 번째 노드, head->prev는 마지막 노드를 가리킨다.
append 시 마지막 노드와 head 사이에 새 노드를 연결한다.
*/
// 테일과 헤드 사이에 새 노드를 삽입한다
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
void append_node(Node **head, Node *new_node)
{
    if (head == NULL || *head == NULL || new_node == NULL)
        return;

    insert_after((*head)->prev, new_node);
}

void insert_after(Node *current, Node *new_node)
{
    if (current == NULL || new_node == NULL)
        return;

    new_node->prev = current;
    new_node->next = current->next;
    current->next->prev = new_node;
    current->next = new_node;
}

void print_node(Node *head)
{
    if (head == NULL)
        return;

    Node *current = head->next;
    while (current != head)
    {
        putchar(current->data.ch);
        current = current->next;
    }
    putchar('\n');
}

void destroy_list(Node **head)
{
    if (head == NULL || *head == NULL)
        return;

    Node *current = (*head)->next;

    while (current != *head)
    {
        Node *next = current->next;

        free(current);

        current = next;
    }
    free(*head);
    *head = NULL;
}

void remove_node(Node *target)
{
    if (target == NULL)
        return;

    target->prev->next = target->next;
    target->next->prev = target->prev;
    target->prev = NULL;
    target->next = NULL;
    free(target);
}
