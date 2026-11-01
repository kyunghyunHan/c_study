#ifndef SLL_H
#define SLL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct _data
{
    int id;
    int score;
} data_t;
typedef struct nodeSLL
{
    data_t data;
    struct nodeSLL *next;
} nodeSLL;

nodeSLL *create_nodeSLL(data_t *data);
void append_nodeSLL(nodeSLL *head, nodeSLL *newnode);
void print_nodeSLL(nodeSLL *head);
void destroy_list(nodeSLL *head);
#endif
