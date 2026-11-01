#include "circular_queue.h"

void cq_create_queue(CircularQueue **queue, int capacity)
{ // queue를 heap에저장
    if (queue == NULL || capacity <= 0)
    {
        return;
    }

    *queue = NULL;

    (*queue) = (CircularQueue *)malloc(sizeof(CircularQueue));
    if (*queue == NULL)
    {
        return;
    }

    //
    (*queue)->nodes = (Node *)malloc(sizeof(Node) * (capacity + 1));
    if ((*queue)->nodes == NULL)
    {
        free(*queue);
        *queue = NULL;
        return;
    }
    (*queue)->capacity = capacity;
    (*queue)->front = 0;
    (*queue)->rear = 0;
}

void cq_destroy_queue(CircularQueue *queue)
{
    if (queue == NULL)
    {
        return;
    }

    free(queue->nodes);
    free(queue);
}

void cq_enque(CircularQueue *queue, ElementType data)
{
    if (queue == NULL || cq_is_full(queue))
    {
        return;
    }

    int postion = 0;
    if (queue->rear == queue->capacity)
    {
        postion = queue->rear;
        queue->rear = 0;
    }
    else
    {
        postion = queue->rear++;
    }
    queue->nodes[postion].data = data;
}

ElementType cq_dequeue(CircularQueue *queue)
{
    if (queue == NULL || cq_is_empty(queue))
    {
        return 0;
    }

    int postion = queue->front;
    if (queue->front == queue->capacity)
    {
        queue->front = 0;
    }
    else
    {
        queue->front++;
    }
    return queue->nodes[postion].data;
}

int cq_get_size(CircularQueue *queue)
{
    if (queue == NULL)
    {
        return 0;
    }

    if (queue->front <= queue->rear)
    {
        return queue->rear - queue->front;
    }
    else
    {
        return (queue->capacity - queue->front) + queue->rear + 1;
    }
}

int cq_is_empty(CircularQueue *queue)
{
    return queue == NULL || (queue->front == queue->rear);
}

int cq_is_full(CircularQueue *queue)
{
    if (queue == NULL)
    {
        return 0;
    }

    if (queue->front < queue->rear)
    {
        return (queue->rear - queue->front) == queue->capacity;
    }
    else
    {
        return (queue->rear + 1) == queue->front;
    }
}

int main(void)
{
    int i;
    CircularQueue *queue = NULL;
    cq_create_queue(&queue, 10);
    if (queue == NULL)
    {
        return 1;
    }

    cq_enque(queue, 1);
    cq_enque(queue, 2);
    cq_enque(queue, 3);
    cq_enque(queue, 4);

    for (int i = 0; i < 3; i++)
    {
        printf("Deque: %d, ", cq_dequeue(queue));
        printf("Front:%d, Rear:%d\n", queue->front, queue->rear);
    }

    i = 100;
    while (cq_is_full(queue) == 0)
    {
        cq_enque(queue, i++);
    }

    printf("Capacity: %d, Size: %d\n\n", queue->capacity, cq_get_size(queue));

    while (cq_is_empty(queue) == 0)
    {
        printf("Daeue: %d,", cq_dequeue(queue));
        printf("Front:%d, Rear:%d\n", queue->front, queue->rear);
    }

    cq_destroy_queue(queue);

    return 0;
}
