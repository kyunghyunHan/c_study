#ifndef MST_H
#define MST_H

#include "../graph.h"

Graph *mst_prim(const Graph *graph, const Vertex *start_vertex);
Graph *mst_kruskal(const Graph *graph);
int mst_total_weight(const Graph *tree);
void mst_print(const Graph *tree);

#endif
