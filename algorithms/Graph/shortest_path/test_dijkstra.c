#include "dijkstra.h"

#include <stdlib.h>

int main(void)
{
    Graph *graph = create_graph();

    Vertex *vertex_a = create_vertex('A');
    Vertex *vertex_b = create_vertex('B');
    Vertex *vertex_c = create_vertex('C');
    Vertex *vertex_d = create_vertex('D');
    Vertex *vertex_e = create_vertex('E');
    Vertex *vertex_f = create_vertex('F');

    add_vertex(graph, vertex_a);
    add_vertex(graph, vertex_b);
    add_vertex(graph, vertex_c);
    add_vertex(graph, vertex_d);
    add_vertex(graph, vertex_e);
    add_vertex(graph, vertex_f);

    add_edge(vertex_a, create_edge(vertex_a, vertex_b, 4));
    add_edge(vertex_a, create_edge(vertex_a, vertex_c, 2));
    add_edge(vertex_b, create_edge(vertex_b, vertex_d, 5));
    add_edge(vertex_c, create_edge(vertex_c, vertex_b, 1));
    add_edge(vertex_c, create_edge(vertex_c, vertex_d, 8));
    add_edge(vertex_c, create_edge(vertex_c, vertex_e, 10));
    add_edge(vertex_d, create_edge(vertex_d, vertex_e, 2));
    add_edge(vertex_d, create_edge(vertex_d, vertex_f, 6));
    add_edge(vertex_e, create_edge(vertex_e, vertex_f, 2));

    int *distance = malloc(sizeof(int) * (size_t)graph->vertex_count);
    int *previous = malloc(sizeof(int) * (size_t)graph->vertex_count);

    if (distance == NULL || previous == NULL)
    {
        free(distance);
        free(previous);
        detroy_graph(graph);
        return 1;
    }

    if (!dijkstra_shortest_path(graph, vertex_a, distance, previous))
    {
        printf("다익스트라 실행에 실패했습니다.\n");
        free(distance);
        free(previous);
        detroy_graph(graph);
        return 1;
    }

    dijkstra_print_result(graph, vertex_a, distance, previous);

    free(distance);
    free(previous);
    detroy_graph(graph);

    return 0;
}
