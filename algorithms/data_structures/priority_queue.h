#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int PriorityType;
typedef struct Node
{
    PriorityType priority;
    void *data;
} Node;

typedef struct PriorityQueue
{
    Node *nodes;
    int capacity;
    int used_size;
} PriorityQueue;

PriorityQueue *pq_create(int initial_size);

void pq_destroy(PriorityQueue *pq);

void pq_enqueue(PriorityQueue *pq, Node new_data);

void pq_dequeue(PriorityQueue *pq, Node *root);

int pq_get_parent(int index);

int pq_get_left_child(int index);

void pq_swap_nodes(PriorityQueue *pq, int index1, int index2);

int pq_is_empty(PriorityQueue *pq);

#endif