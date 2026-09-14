#include "heap.h"

Heap *heap_create(int initial_size)
{
    Heap *new_heap = (Heap *)malloc(sizeof(Heap));
    new_heap->capacity = initial_size;
    new_heap->used_size = 0;
    new_heap->nodes = (Node *)malloc(sizeof(Node) * new_heap->capacity);

    printf("size : %d\n", sizeof(Node));
    return new_heap;
}
void heap_destroy(Heap *h)
{
    free(h->nodes);
    free(h);
}
void heap_insert(Heap *h, ElementType new_data)
{
    int current_position = h->used_size;
    int parent_postion = heap_get_parent(current_position);

    if (h->used_size == h->capacity)
    {
        h->capacity *= 2;
        h->nodes = (Node *)realloc(h->nodes, sizeof(Node) * h->capacity);
    }

    h->nodes[current_position].data = new_data;
    // 후속처리

    while (current_position > 0 && h->nodes[current_position].data < h->nodes[parent_postion].data)
    {
        heap_swap_nodes(h, current_position, parent_postion);
        current_position = parent_postion;
        parent_postion = heap_get_parent(current_position);
    }
    h->used_size++;
}
void heap_delete_min(Heap *h, Node *root)
{
    int parent_position = 0;
    int left_position = 0;
    int right_position = 0;
    memcpy(root, &h->nodes[0], sizeof(Node));
    memset(&h->nodes[0], 0, sizeof(Node));

    h->used_size--;
    heap_swap_nodes(h, 0, h->used_size);

    left_position = heap_get_left_child(0);
    right_position = left_position + 1;

    while (1)
    {

        int selected_child = 0;

        if (left_position >= h->used_size)
        {
            break;
        }
        if (right_position >= h->used_size)
        {
            selected_child = left_position;
        }
        else
        {
            if (h->nodes[left_position].data > h->nodes[right_position].data)
            {
                selected_child = right_position;
            }
            else
            {
                selected_child = left_position;
            }
        }
        if (h->nodes[selected_child].data < h->nodes[parent_position].data)
        {
            heap_swap_nodes(h, parent_position, selected_child);
            parent_position = selected_child;
        }
        else
        {
            break;
        }
        left_position = heap_get_left_child(parent_position);
        right_position = left_position + 1;
    }
    if (h->used_size < (h->capacity / 2))
    {
        h->capacity /= 2;
        h->nodes = (Node *)realloc(h->nodes, sizeof(Node) * h->capacity);
    }
}

int heap_get_parent(int index)
{
    return (int)((index - 1) / 2);
}
int heap_get_left_child(int index)
{
    return (2 * index) + 1;
}
void heap_swap_nodes(Heap *h, int index1, int index2)
{
    int copy_size = sizeof(Node);
    Node *temp = (Node *)malloc(copy_size);

    memcpy(temp, &h->nodes[index1], copy_size);
    memcpy(&h->nodes[index1], &h->nodes[index2], copy_size);
    memcpy(&h->nodes[index2], temp, copy_size);
    free(temp);
}
void heap_print_nodes(Heap *h)
{
    int i = 0;
    for (i = 0; i < h->used_size; i++)
    {
        printf("%d ", h->nodes[i].data);
    }
    printf("%\n");
}
