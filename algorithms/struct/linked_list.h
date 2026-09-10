#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef int ElementType;

typedef struct tagNode
{
    ElementType data;
    struct tagNode *next_node;
} Node;

Node *sll_create_node(ElementType new_data);
void sll_destroy_node(Node *node);
void sll_append_node(Node **head, Node *new_node);
Node *sll_get_node_at(Node *head, int location);
void sll_remove_node(Node **head, Node *remove);
void sll_insert_after(Node *current, Node *new_node);
void sll_insert_new_head(Node **head, Node *new_head);
int sll_get_node_count(Node *head);

#endif
