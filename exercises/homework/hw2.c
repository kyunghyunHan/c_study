#include <stdio.h>
#include <stdlib.h>
typedef struct _Data
{
    int id;
    int score;
} Data;

typedef struct _Node
{
    Data data;
    struct _Node *next_node;
} Node;

typedef struct Queue
{
    Node *front;
    Node *rear;
    int count;
    int size;

} Queue;
Queue *init(int s)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));

    if (queue == NULL)
    {
        return NULL;
    }
    Node *dummy = malloc(sizeof(Node));
    if (dummy == NULL)
    {
        free(queue);
        return NULL;
    }
    // (*queue).front = NULL;
    // (*queue).rear = NULL;
    (*queue).front = dummy;
    (*queue).rear = dummy;
    dummy->next_node = dummy; // 더미버전
    (*queue).count = 0;
    (*queue).size = s;
    return queue;
}
Node *create_node(Data data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        return NULL;
    }
    new_node->data = data;
    new_node->next_node = NULL;
    return new_node;
}
void enqueue(Queue *queue, Node *new_node)
{
    if (queue == NULL || new_node == NULL)
    {
        return;
    }
    // if ((*queue).count == 0)
    // {
    //     (*queue).front = new_node;
    //     (*queue).rear = new_node;
    //     (*new_node).next_node = new_node;
    // }
    // else
    // {
    (*(*queue).rear).next_node = new_node;
    (*queue).rear = new_node;
    (*(*queue).rear).next_node = (*queue).front; // 환형
    // }
    (*queue).count++;
}
Node *dequeue(Queue *queue)
{
    if (queue == NULL || (*queue).front == NULL)
    {
        printf("UnderFlow\n");
        return NULL;
    }

    // Node *remove = (*queue).front;
    Node *remove = queue->front->next_node;
    // 더미가 remove 다음 노드를 가리키게
    queue->front->next_node = remove->next_node;

    // 마지막 데이터 노드를 삭제했다면
    if (queue->rear == remove)
    {
        queue->rear = queue->front;
    }
    // if ((*queue).front == (*queue).rear)
    // {
    //     (*queue).front = NULL;
    //     (*queue).rear = NULL;
    // }
    // else
    // {
    //     (*queue).front = (*(*queue).front).next_node;

    //     (*queue).rear->next_node = (*queue).front;

    //     (*remove).next_node = NULL;
    // }
    (*queue).count--;
    return remove;
}
void destroy_node(Node *node)
{
    if (node == NULL)
        return;

    free(node);
}
void destroy_queue(Queue *queue)
{
    if (queue == NULL)
        return;

    free(queue);
}

void printq(Queue *queue)
{
    if (queue == NULL)
    {
        return;
    }
    Node *target = queue->front->next_node;
    // Node *target = (*queue).front;
    int i = 0;
    while (i < (*queue).count)
    {
        printf("%d %d\n", (*target).data.id, (*target).data.score);
        target = (*target).next_node;
        i++;
    }
}
int main(void)
{

    int s, n, r, c;
    int count = 0;
    char cmd;

    (void)freopen("sandbox/data.txt", "r", stdin);
    if (scanf("%d %d", &s, &n) != 2)
        return 1;

    Queue *queue = init(s);

    if (queue == NULL)
        return 1;

    while (count < n && scanf(" %c", &cmd) == 1)
    {
        if (cmd == 'P')
        {
            if (scanf("%d %d", &r, &c) != 2)
                break;
            Node *new_node = create_node((Data){r, c});
            enqueue(queue, new_node);
        }
        else if (cmd == 'D')
        {
            Node *removed = dequeue(queue);
            destroy_node(removed);
        }
    }
    printq(queue);
    destroy_queue(queue);

    return 0;
}