#include "02_SLL.h"

#include <stdio.h>
#include <stdlib.h>

NodeSLL *sll_create_node(data_t *data)
{
    NodeSLL *new_node = calloc(1, sizeof(NodeSLL));

    if (new_node != NULL)
    {
        new_node->data = *data;
    }

    return new_node;
}

void sll_append_node(NodeSLL **head, NodeSLL *new_node)
{
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        NodeSLL *tail = *head;
        // for (NodeSLL *tail = *head; tail->next_node != NULL; tail = tail->next_node)
        ;
        while ((tail->next_node) != NULL)
        {
            tail = (*tail).next_node;
        }

        (*tail).next_node = new_node;
    }
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
