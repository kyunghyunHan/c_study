#include "graph.h"

int main(void)
{
    Graph *g = create_graph();

    Vertex *v1 = create_vertex('1');
    Vertex *v2 = create_vertex('2');
    Vertex *v3 = create_vertex('3');
    Vertex *v4 = create_vertex('4');
    Vertex *v5 = create_vertex('5');

    add_vertex(g, v1);
    add_vertex(g, v2);
    add_vertex(g, v3);
    add_vertex(g, v4);
    add_vertex(g, v5);

    add_edge(v1, create_edge(v1, v2, 0));
    add_edge(v1, create_edge(v1, v3, 0));
    add_edge(v1, create_edge(v1, v4, 0));
    add_edge(v1, create_edge(v1, v5, 0));

    add_edge(v2, create_edge(v2, v1, 0));
    add_edge(v2, create_edge(v2, v3, 0));
    add_edge(v2, create_edge(v2, v5, 0));

    add_edge(v3, create_edge(v3, v1, 0));
    add_edge(v3, create_edge(v3, v2, 0));

    add_edge(v4, create_edge(v4, v1, 0));
    add_edge(v4, create_edge(v4, v5, 0));

    add_edge(v5, create_edge(v5, v1, 0));

    print_graph(g);

    detroy_graph(g);

    return 0;
}
