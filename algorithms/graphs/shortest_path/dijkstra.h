#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../graph.h"

int dijkstra_shortest_path(
    const Graph *graph,
    const Vertex *start_vertex,
    int *distance,
    int *previous);

void dijkstra_print_result(
    const Graph *graph,
    const Vertex *start_vertex,
    const int *distance,
    const int *previous);

#endif
