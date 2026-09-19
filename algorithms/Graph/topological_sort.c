#include "topological_sort.h"

void topological_sort(Vertex *vertex, Node **list)
{
    while (vertex != NULL)
    {
        if (vertex->visited == NotVisted)
        {
            ts_dfs(vertex, list);
        }

        vertex = vertex->next;
    }
}

void ts_dfs(Vertex *vertex, Node **list)
{
    Node *new_head = NULL;
    Edge *edge = NULL;

    vertex->visited = Visited;

    edge = vertex->adjacenc_list;

    while (edge != NULL)
    {
        if (edge->target != NULL && edge->target->visited == NotVisted)
        {
            ts_dfs(edge->target, list);
        }

        edge = edge->next;
    }

    printf("%c\n", vertex->data);
    new_head = sll_create_node(vertex);
    sll_insert_new_head(list, new_head);
}
