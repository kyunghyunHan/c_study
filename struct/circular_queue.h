#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct
{
    ElementType data;
} Node;

typedef struct
{
    int capacity;
    int front;
    int rear;
    Node *nodes;

} CircularQueue;

void cq_create_queue(CircularQueue **queue, int capacity);
void cq_destroy_queue(CircularQueue *queue);
void cq_enque(CircularQueue *queue, ElementType data);
ElementType cq_dequeue(CircularQueue *queue);
int cq_get_size(CircularQueue *queue);
int cq_is_empty(CircularQueue *queue);
int cq_is_full(CircularQueue *queue);

#endif
