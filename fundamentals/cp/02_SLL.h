#ifndef SLL_H
#define SLL_H

#include <stdbool.h>
#include <stddef.h>
typedef struct _data
{
    int id;
    int score;
} data_t;
typedef struct NodeSLL
{
    data_t data;
    struct NodeSLL *next_node;
} NodeSLL;

NodeSLL *sll_create_node(data_t *data);
void sll_append_node()
{
}


#endif
