#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    char *data;
    struct Node *next_node;
} Node;

typedef struct LinkedQueue
{
    Node *front;
    Node *rear;
    int count;
} LinkedQueue;

void lq_create_queue(LinkedQueue **queue);
void lq_destroy_queue(LinkedQueue *queue);

Node *lq_create_node(const char *data);
void lq_destroy_node(Node *node);

void lq_enqueue(LinkedQueue *queue, Node *new_node);
Node *lq_dequeue(LinkedQueue *queue);

int lq_is_empty(LinkedQueue *queue);

#endif
