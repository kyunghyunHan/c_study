#include "graph.h"

Graph *create_graph(void)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    (*graph).vertices = NULL;
    (*graph).vertex_count = 0;

    return graph;
}

void detroy_graph(Graph *g)
{
    while ((*g).vertices != NULL)
    {
        Vertex *vertices = (*(*g).vertices).next;
        detroy_vertex((*g).vertices);
        (*g).vertices = vertices;
    }
    free(g);
}
Vertex *create_vertex(VElementType data)
{
    Vertex *v = (Vertex *)malloc(sizeof(Vertex));
    (*v).data = data;
    (*v).next = NULL;
    (*v).adjacenc_list = NULL;
    (*v).visited = NotVisted;
    (*v).index = -1;

    return v;
}
void detroy_vertex(Vertex *v)
{
    while (v->adjacenc_list != NULL)
    {
        Edge *edge = v->adjacenc_list->next;
        detroy_edge(v->adjacenc_list);
        v->adjacenc_list = edge;
    }
    free(v);
}
Edge *create_edge(Vertex *from, Vertex *target, int weight)
{
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->from = from;
    e->target = target;
    e->next = NULL;
    e->weight = weight;
    return e;
}
void detroy_edge(Edge *e)
{
    free(e);
}

void add_vertex(Graph *g, Vertex *v)
{
    Vertex *vertex_list = g->vertices;

    if (vertex_list == NULL)
    {
        g->vertices = v;
    }
    else
    {
        while (vertex_list->next != NULL)
        {
            vertex_list = vertex_list->next;
        }
        vertex_list->next = v;
    }

    v->index = g->vertex_count++;
}
void add_edge(Vertex *v, Edge *e)
{
    if (v->adjacenc_list == NULL)
    {
        v->adjacenc_list = e;
    }
    else
    {
        Edge *adjacency_list = v->adjacenc_list;
        while (adjacency_list->next != NULL)
        {
            adjacency_list = adjacency_list->next;
        }
        adjacency_list->next = e;
    }
}
void print_graph(Graph *g)
{
    Vertex *v = NULL;
    Edge *e = NULL;

    if ((v = g->vertices) == NULL)
    {
        return;
    }

    while (v != NULL)
    {
        printf("%c : ", v->data);

        e = v->adjacenc_list;

        while (e != NULL)
        {
            printf("%c ", e->target->data);
            e = e->next;
        }

        printf("\n");
        v = v->next;
    }
}
