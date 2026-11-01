#ifndef SQ_03_H
#define SQ_03_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    int r;
    int c;
} Node;
typedef struct _Stack
{
    int capacity;
    int top; // 데이터는 top-1까지 있음

    Node *nodes;
} Stack;

int enqueue(Stack *queue, Stack node);
int dequeue(Stack *queue);
void print_q(const Stack *queue);
Stack *init_queue(int capacity);
void destroy_queue(Stack *queue);

#endif
