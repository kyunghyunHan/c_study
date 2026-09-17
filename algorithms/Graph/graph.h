#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

enum VisitMode
{
    Visited,
    NotVisted
};

typedef int VElementType;

typedef struct _Vertex Vertex;
typedef struct _Edge Edge;

struct _Vertex
{
    VElementType data;
    int visited;
    int index;

    Vertex *next;
    Edge *adjacenc_list;

};

struct _Edge
{
    int weight;
    Edge *next;
    Vertex *from;
    Vertex *target;
};

typedef struct _Graph
{
    Vertex *vertices;
    int vertex_count;
} Graph;

Graph *create_graph(void);
void detroy_graph(Graph *g);
Vertex *create_vertex(VElementType data);
void detroy_vertex(Vertex *v);
Edge *create_edge(Vertex *from, Vertex *target, int weight);
void detroy_edge(Edge *e);

void add_vertex(Graph *g, Vertex *v);
void add_edge(Vertex *v, Edge *e);
void print_graph(Graph *g);

#endif
