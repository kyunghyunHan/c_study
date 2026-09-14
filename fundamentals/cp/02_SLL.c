#include "02_SLL.h"

#include <stdio.h>
#include <stdlib.h>

nodeSLL *Create_nodeSLL(data_t *data)
{
    nodeSLL *newnode = NULL;
    newnode = (nodeSLL *)calloc(1, sizeof(nodeSLL));
    if (newnode != NULL)
        newnode->data = *data;
    return newnode;
}

void Append_nodeSLL(nodeSLL *head, nodeSLL *newnode)
{
    nodeSLL *curr = head;
    for (; curr->next != NULL; curr = curr->next)
        ;
    curr->next = newnode;
    return;
}

void Print_nodeSLL(nodeSLL *head)
{
    nodeSLL *curr = head;
    for (; curr != NULL; curr = curr->next)
    {
        printf("%d %d\n", curr->data.id, curr->data.score);
    }
    return;
}
// bool sll_push_front(NodeSLL **head, int data)
// {
//     NodeSLL *node;

//     if (head == NULL)
//     {
//         return false;
//     }

//     node = sll_create_node(data);
//     if (node == NULL)
//     {
//         return false;
//     }

//     node->next = *head;
//     *head = node;
//     return true;
// }

// bool sll_push_back(NodeSLL **head, int data)
// {
//     NodeSLL *node;
//     NodeSLL *current;

//     if (head == NULL)
//     {
//         return false;
//     }

//     node = sll_create_node(data);
//     if (node == NULL)
//     {
//         return false;
//     }

//     if (*head == NULL)
//     {
//         *head = node;
//         return true;
//     }

//     current = *head;
//     while (current->next != NULL)
//     {
//         current = current->next;
//     }
//     current->next = node;
//     return true;
// }

// NodeSLL *sll_find(NodeSLL *head, int data)
// {
//     while (head != NULL)
//     {
//         if (head->data == data)
//         {
//             return head;
//         }
//         head = head->next;
//     }
//     return NULL;
// }

// bool sll_remove(NodeSLL **head, int data)
// {
//     NodeSLL **current;
//     NodeSLL *removed;

//     if (head == NULL)
//     {
//         return false;
//     }

//     current = head;
//     while (*current != NULL && (*current)->data != data)
//     {
//         current = &(*current)->next;
//     }

//     if (*current == NULL)
//     {
//         return false;
//     }

//     removed = *current;
//     *current = removed->next;
//     free(removed);
//     return true;
// }

// size_t sll_length(const NodeSLL *head)
// {
//     size_t length = 0;

//     while (head != NULL)
//     {
//         ++length;
//         head = head->next;
//     }
//     return length;
// }

// void sll_print(const NodeSLL *head)
// {
//     while (head != NULL)
//     {
//         printf("%d -> ", head->data);
//         head = head->next;
//     }
//     puts("NULL");
// }

// void sll_clear(NodeSLL **head)
// {
//     NodeSLL *current;

//     if (head == NULL)
//     {
//         return;
//     }

//     while (*head != NULL)
//     {
//         current = *head;
//         *head = current->next;
//         free(current);
//     }
// }
