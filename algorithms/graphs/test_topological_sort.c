#include "graph.h"
#include "topological_sort.h"

int main(void)
{
    Node *sorted_list = NULL;
    Node *current_node = NULL;

    //  그래프 생성
    Graph *graph = create_graph();

    //  정점 생성

    Vertex *vertex_a = create_vertex('A');
    Vertex *vertex_b = create_vertex('B');
    Vertex *vertex_c = create_vertex('C');
    Vertex *vertex_d = create_vertex('D');
    Vertex *vertex_e = create_vertex('E');
    Vertex *vertex_f = create_vertex('F');
    Vertex *vertex_g = create_vertex('G');
    Vertex *vertex_h = create_vertex('H');

    //  그래프에 정점을 추가
    add_vertex(graph, vertex_a);
    add_vertex(graph, vertex_b);
    add_vertex(graph, vertex_c);
    add_vertex(graph, vertex_d);
    add_vertex(graph, vertex_e);
    add_vertex(graph, vertex_f);
    add_vertex(graph, vertex_g);
    add_vertex(graph, vertex_h);

    //  정점과 정점을 간선으로 잇기
    add_edge(vertex_a, create_edge(vertex_a, vertex_c, 0));
    add_edge(vertex_a, create_edge(vertex_a, vertex_d, 0));

    add_edge(vertex_b, create_edge(vertex_b, vertex_c, 0));
    add_edge(vertex_b, create_edge(vertex_b, vertex_e, 0));

    add_edge(vertex_c, create_edge(vertex_c, vertex_f, 0));

    add_edge(vertex_d, create_edge(vertex_d, vertex_f, 0));
    add_edge(vertex_d, create_edge(vertex_d, vertex_g, 0));

    add_edge(vertex_e, create_edge(vertex_e, vertex_g, 0));

    add_edge(vertex_f, create_edge(vertex_f, vertex_h, 0));

    add_edge(vertex_g, create_edge(vertex_g, vertex_h, 0));

    //  위상 정렬
    topological_sort(graph->vertices, &sorted_list);

    printf("Topological Sort Result : ");

    current_node = sorted_list;

    while (current_node != NULL)
    {
        printf("%c ", current_node->data->data);
        current_node = current_node->next_node;
    }
    printf("\n");

    while (sorted_list != NULL)
    {
        current_node = sorted_list;
        sorted_list = sorted_list->next_node;
        sll_destroy_node(current_node);
    }

    //  그래프 소멸
    detroy_graph(graph);

    return 0;
}
