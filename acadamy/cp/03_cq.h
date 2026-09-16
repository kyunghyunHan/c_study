#ifndef CQ_03_H
#define CQ_03_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    int r;
    int c;
} Node;
typedef struct _Queue
{
    int capacity;
    int front;
    int rear;

    Node *nodes;
} Queue;

int enqueue(Queue *queue, Node node);
int dequeue(Queue *queue);
void print_q(const Queue *queue);
Queue *init_queue(int capacity);
void destroy_queue(Queue *queue);

#endif
