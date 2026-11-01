#include "linked_queue.h"

void lq_create_queue(LinkedQueue **queue)
{
    if (queue == NULL)
    {
        return;
    }

    *queue = (LinkedQueue *)malloc(sizeof(LinkedQueue));
    if (*queue == NULL)
    {
        return;
    }

    (*queue)->front = NULL;
    (*queue)->rear = NULL;
    (*queue)->count = 0;
}
void lq_destroy_queue(LinkedQueue *queue)
{
    if (queue == NULL)
    {
        return;
    }

    while (!lq_is_empty(queue))
    {
        Node *popped = lq_dequeue(queue);
        lq_destroy_node(popped);
    }

    // 큐를 heap 에서 할당 헤제
    free(queue);
}

Node *lq_create_node(const char *data)
{
    if (data == NULL)
    {
        return NULL;
    }

    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        return NULL;
    }

    new_node->data = (char *)malloc(strlen(data) + 1);
    if (new_node->data == NULL)
    {
        free(new_node);
        return NULL;
    }

    strcpy(new_node->data, data); // 데이터 저장
    new_node->next_node = NULL;   // 다름 노드에 대한 포인터는 NULL로 초기화
    return new_node;
}
void lq_destroy_node(Node *node)
{
    if (node == NULL)
    {
        return;
    }

    free(node->data);
    free(node);
}

void lq_enqueue(LinkedQueue *queue, Node *new_node)
{
    if (queue == NULL || new_node == NULL)
    {
        return;
    }

    if (queue->front == NULL)
    {
        queue->front = new_node;
        queue->rear = new_node;
        queue->count++;
    }
    else
    {
        queue->rear->next_node = new_node;
        queue->rear = new_node;
        queue->count++;
    }
}

Node *lq_dequeue(LinkedQueue *queue)
{
    if (queue == NULL || queue->front == NULL)
    {
        return NULL;
    }

    // lq_dequeue함수가 반활할 최상의 노드
    Node *front = queue->front;
    if (queue->front->next_node == NULL)
    {
        queue->front = NULL;
        queue->rear = NULL;
    }
    else
    {
        queue->front = queue->front->next_node;
    }
    queue->count--;
    return front;
}

int lq_is_empty(LinkedQueue *queue)
{
    return queue == NULL || (queue->front == NULL);
}
int main(void)
{
    Node *popped;
    LinkedQueue *queue = NULL;

    lq_create_queue(&queue);
    if (queue == NULL)
    {
        return 1;
    }

    lq_enqueue(queue, lq_create_node("abc"));
    lq_enqueue(queue, lq_create_node("def"));
    lq_enqueue(queue, lq_create_node("efg"));
    lq_enqueue(queue, lq_create_node("hij"));

    printf("Queue Size : %d\n", queue->count);

    while (lq_is_empty(queue) == 0)
    {
        popped = lq_dequeue(queue);
        printf("Dequeue : %s \n", popped->data);
        lq_destroy_node(popped);
    }
    lq_destroy_queue(queue);

    return 0;
}
