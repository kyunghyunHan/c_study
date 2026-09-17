#include <stdio.h>
#include <stdlib.h>

typedef struct _nodeQ
{
    int r;
    int c;
    struct _nodeQ *next;
} nodeQ;

typedef struct _queue_t
{
    nodeQ *front;
    nodeQ *rear;
    nodeQ dummy;
} queue_t;

queue_t *init_Q(int size)
{
    (void)size;
    queue_t *nq = (queue_t *)malloc(sizeof(queue_t));
    if (nq == NULL)
        return NULL;

    nq->dummy.c = 0;
    nq->dummy.r = 0;

    nq->dummy.next = NULL;
    nq->front = &nq->dummy;
    nq->rear = &nq->dummy;

    return nq;
}

int Enqueue(queue_t *q, nodeQ newdata)
{
    nodeQ *node = malloc(sizeof(nodeQ));
    if (node == NULL)
    {
        printf("Overflow!\n");
        return 0;
    }
    *node = newdata;

    q->rear->next = node;
    q->rear = node;

    return 1;
}

nodeQ *Dequeue(queue_t *q)
{
    if (q->front->next == NULL)
    {
        printf("Underflow!\n");
        return NULL;
    }
    nodeQ *old = q->front->next;
    q->front->next = old->next;
    if (old == q->rear)
        q->rear = q->front;

    return old;
}

void printQ(queue_t *q)
{
    int i = 0;
    for (nodeQ *p = q->front->next; p != NULL; p = p->next)
    {
        printf("%d : %d %d\n", i++, p->r, p->c);
    }
}

void free_Q(queue_t *q)
{
    nodeQ *p = q->front->next;
    while (p != NULL)
    {
        nodeQ *next = p->next;
        free(p);
        p = next;
    }
    free(q);
}

int main(void)
{
    queue_t *queue = NULL;
    char cmd;
    int n, s;
    int r, c;
    int i;

    (void)freopen("qdata.txt", "r", stdin);
    (void)scanf("%d %d", &s, &n);
    queue = init_Q(s);

    for (i = 0; i < n; ++i)
    {
        (void)scanf(" %c", &cmd);
        if (cmd == 'P')
        {
            (void)scanf("%d %d", &r, &c);
            if (!Enqueue(queue, (nodeQ){r, c, NULL}))
                break;
        }
        else
        {
            nodeQ *popped = Dequeue(queue);
            if (!popped)
                break;
            free(popped);
        }
    }
    printQ(queue);
    free_Q(queue);
    return 0;
}