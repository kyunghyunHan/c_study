#include "03_cq.h"
/*
나갈곳
*/
Queue *init_queue(int s)
{
    if (s <= 0)
        return NULL;

    int capacity = s + 1;
    Queue *queue = malloc(sizeof(Queue) +
                          sizeof(Node) * capacity);
    if (queue == NULL)
        return NULL;

    (*queue).capacity = capacity;
    (*queue).front = 0;
    (*queue).rear = 0;
    (*queue).nodes = (Node *)(queue + 1);

    return queue;
}

int enqueue(Queue *queue, Node node)
{

    int next_rear = queue->rear + 1;

    if (next_rear == queue->capacity)
    {
        next_rear = 0;
    }
    
    if (next_rear == (*queue).front)
    {
        printf("OverFlow\n");
        return 0;
    }

    (*queue).nodes[(*queue).rear] = node;
    (*queue).rear = next_rear;

    return 1;
}

int dequeue(Queue *queue)
{
    if ((*queue).front == (*queue).rear)
    {
        printf("UnderFlow\n");
        return 0;
    }

    (*queue).front = ((*queue).front + 1) % (*queue).capacity;
    return 1;
}

void print_q(const Queue *queue)
{
    int index = (*queue).front;
    int count = 0;

    while (index != (*queue).rear)
    {
        printf("%d : %d %d\n", count,
               (*queue).nodes[index].r,
               (*queue).nodes[index].c);

        index = (index + 1) % (*queue).capacity;
        count++;
    }
}

void destroy_queue(Queue *queue)
{
    if (queue == NULL)
        return;

    free(queue);
}
