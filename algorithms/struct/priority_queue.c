#include "priority_queue.h"

PriorityQueue *pq_create(int intitial_size)
{
    PriorityQueue *new_nq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    new_nq->capacity = intitial_size;
    new_nq->used_size = 0;
    new_nq->nodes = (Node *)malloc(sizeof(Node) * new_nq->capacity);

    return new_nq;
}

void pq_destroy(PriorityQueue *pq)
{
    free(pq->nodes);
    free(pq);
}

void pq_enqueue(PriorityQueue *pq, Node new_node)
{
    int current_position = pq->used_size;
    int parent_position = pq_get_parent(current_position);

    if (pq->used_size == pq->capacity)
    {
        if (pq->capacity == 0)
            pq->capacity = 1;

        pq->capacity *= 2;
        pq->nodes = (Node *)realloc(
            pq->nodes,
            sizeof(Node) * pq->capacity);
    }

    pq->nodes[current_position] = new_node;

    while (current_position > 0 &&
           pq->nodes[current_position].priority <
               pq->nodes[parent_position].priority)
    {
        pq_swap_nodes(pq, current_position, parent_position);

        current_position = parent_position;
        parent_position = pq_get_parent(current_position);
    }

    pq->used_size++;
}

void pq_swap_nodes(PriorityQueue *pq, int index1, int index2)
{
    int copy_size = sizeof(Node);
    Node *temp = (Node *)malloc(copy_size);

    memcpy(temp, &pq->nodes[index1], copy_size);
    memcpy(&pq->nodes[index1], &pq->nodes[index2], copy_size);
    memcpy(&pq->nodes[index2], temp, copy_size);

    free(temp);
}

void pq_dequeue(PriorityQueue *pq, Node *root)
{
    int parent_position = 0;
    int left_position = 0;
    int right_position = 0;

    memcpy(root, &pq->nodes[0], sizeof(Node));
    memset(&pq->nodes[0], 0, sizeof(Node));

    pq->used_size--;
    pq_swap_nodes(pq, 0, pq->used_size);

    left_position = pq_get_left_child(0);
    right_position = left_position + 1;

    while (1)
    {
        int selected_child = 0;

        if (left_position >= pq->used_size)
            break;

        if (right_position >= pq->used_size)
        {
            selected_child = left_position;
        }
        else
        {
            if (pq->nodes[left_position].priority >
                pq->nodes[right_position].priority)
                selected_child = right_position;
            else
                selected_child = left_position;
        }

        if (pq->nodes[selected_child].priority <
            pq->nodes[parent_position].priority)
        {
            pq_swap_nodes(pq, parent_position, selected_child);
            parent_position = selected_child;
        }
        else
            break;

        left_position = pq_get_left_child(parent_position);
        right_position = left_position + 1;
    }

    if (pq->used_size < (pq->capacity / 2))
    {
        pq->capacity /= 2;
        pq->nodes = (Node *)realloc(
            pq->nodes,
            sizeof(Node) * pq->capacity);
    }
}

int pq_get_parent(int index)
{
    return (int)((index - 1) / 2);
}

int pq_get_left_child(int index)
{
    return (2 * index) + 1;
}

int pq_is_empty(PriorityQueue *pq)
{
    return (pq->used_size == 0);
}