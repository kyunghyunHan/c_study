#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct Node
{
    ElementType data;

} Node;

typedef struct Heap
{
    Node *nodes;
    int capacity;
    int used_size;
} Heap;

Heap *heap_create(int initial_size);
void heap_destroy(Heap *h);
void heap_insert(Heap *h, ElementType new_data);
void heap_delete_min(Heap *h, Node *root);
int heap_get_parent(int index);
int heap_get_left_child(int index);
void heap_swap_nodes(Heap *h, int index1, int index2);
void heap_print_nodes(Heap *h);

#endif
