#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#include "graph.h"
#include "linked_list.h"

void topological_sort(Vertex *vertex, Node **list);
void ts_dfs(Vertex *vertex, Node **list);

#endif
