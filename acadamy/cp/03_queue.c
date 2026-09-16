#include "03_queue.h"

Queue *init_queue(int s)
{
    Queue *queue = malloc(sizeof(Queue) +
                          sizeof(Node) * s);
    if (queue == NULL)
        return NULL;

    queue->capacity = s;
    queue->front = 0;
    queue->rear = 0;
    queue->nodes = (Node *)(queue + 1);

    return queue;
}

int enqueue(Queue *queue, Node node)
{
    if ((*queue).rear >= (*queue).capacity)
    {
        printf("OverFlow\n");
        return 0;
    }

    (*queue).nodes[(*queue).rear++] = node;

    return 1;
}
Node *dequeue(Queue *queue)
{
    if ((*queue).front >= (*queue).rear)
    {
        printf("UnderFlow\n");
        return 0;
    }
    (*queue).front++;
    return 1;
    return (*queue).nodes + (*queue).front++;
}
void print_q(const Queue *queue)
{
    for (int i = (*queue).front; i < (*queue).rear; i++)
    {
        printf("%d : %d %d\n", i - (*queue).front,
               (*queue).nodes[i].r, (*queue).nodes[i].c);
    }
}

void destroy_queue(Queue *queue)
{
    if (queue == NULL)
        return;

    free(queue);
}
