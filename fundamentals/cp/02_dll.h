#ifndef DLL_H
#define DLL_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _data
{
    int id;
    int score;
} data_t;
typedef struct tagNode
{
    data_t data;
    struct tagNode *prev_node;
    struct tagNode *next_node;
} Node;

void init_HT(Node **head, Node **tail);


Node *create_node(data_t *data);

#endif /* DLL_H */
