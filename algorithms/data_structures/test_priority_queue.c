#include "priority_queue.h"

void PrintNode(Node *Node)
{
    printf("작업명 : %s (우선순위:%d)\n", Node->data, Node->priority);
}

int main(void)
{
    PriorityQueue *pq = PQ_Create(3);
    Node popped;

    Node nodes[7] =
        {
            {34, (void *)"코딩"},
            {12, (void *)"고객미팅"},
            {87, (void *)"커피타기"},
            {45, (void *)"문서작성"},
            {35, (void *)"디버깅"},
            {66, (void *)"이닦기"}};

    pq_enqueue(pq, nodes[0]);
    pq_enqueue(pq, nodes[1]);
    pq_enqueue(pq, nodes[2]);
    pq_enqueue(pq, nodes[3]);
    pq_enqueue(pq, nodes[4]);
    pq_enqueue(pq, nodes[5]);

    printf("큐에 남아 있는 작업의 수 : %d\n", pq->used_size);

    while (!pq_is_empty(pq))
    {
        pq_dequeue(pq, &popped);
        PrintNode(&popped);
    }

    return 0;
}