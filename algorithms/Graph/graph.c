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
void detroy_vertex(Vertex *v);
Edge *create_edge(Vertex *from, Vertex *target, int weight);
void detroy_edge(Edge *e);

void add_vertex(Graph *g, Vertex *v);
void add_edge(Vertex *v, Edge *e);
void print_graph(Graph *g);
