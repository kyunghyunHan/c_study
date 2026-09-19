#include "graph.h"
#include "linked_queue.h";

void bfs(Vertex *v, LinkedQueue *queue)
{
    Edge *e = NULL;
    printf("%d ", v->data);

    v->visited = Visited;

    lq_enqueue(queue, lq_create_node(v));

    while (!lq_is_empty(queue))
    {
        Node *popped = lq_dequeue(queue);
        v = popped->data;
        e = v->adjacenc_list;

        while (e != NULL)
        {

            v = e->target;

            if (v != NULL && v->visited == NotVisted)
            {
                printf("%d ", v->data);
                v->visited = Visited;
                lq_enqueue(queue, lq_create_node(v));
            }
            e = e->next;
        }
    }
}