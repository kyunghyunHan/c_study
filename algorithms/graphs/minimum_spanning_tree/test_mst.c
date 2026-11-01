#include "mst.h"

static void add_undirected_edge(Vertex *from, Vertex *target, int weight)
{
    add_edge(from, create_edge(from, target, weight));
    add_edge(target, create_edge(target, from, weight));
}

int main(void)
{
    Graph *graph = create_graph();

    Vertex *vertex_a = create_vertex('A');
    Vertex *vertex_b = create_vertex('B');
    Vertex *vertex_c = create_vertex('C');
    Vertex *vertex_d = create_vertex('D');
    Vertex *vertex_e = create_vertex('E');
    Vertex *vertex_f = create_vertex('F');
    Vertex *vertex_g = create_vertex('G');

    add_vertex(graph, vertex_a);
    add_vertex(graph, vertex_b);
    add_vertex(graph, vertex_c);
    add_vertex(graph, vertex_d);
    add_vertex(graph, vertex_e);
    add_vertex(graph, vertex_f);
    add_vertex(graph, vertex_g);

    add_undirected_edge(vertex_a, vertex_b, 3);
    add_undirected_edge(vertex_a, vertex_c, 7);
    add_undirected_edge(vertex_a, vertex_d, 10);
    add_undirected_edge(vertex_b, vertex_c, 2);
    add_undirected_edge(vertex_b, vertex_g, 5);
    add_undirected_edge(vertex_c, vertex_d, 6);
    add_undirected_edge(vertex_c, vertex_e, 4);
    add_undirected_edge(vertex_c, vertex_f, 10);
    add_undirected_edge(vertex_d, vertex_f, 9);
    add_undirected_edge(vertex_e, vertex_f, 2);
    add_undirected_edge(vertex_g, vertex_f, 4);

    Graph *prim_tree = mst_prim(graph, vertex_a);
    Graph *kruskal_tree = mst_kruskal(graph);

    printf("Prim MST\n");
    mst_print(prim_tree);

    printf("\nKruskal MST\n");
    mst_print(kruskal_tree);

    detroy_graph(prim_tree);
    detroy_graph(kruskal_tree);
    detroy_graph(graph);

    return 0;
}
