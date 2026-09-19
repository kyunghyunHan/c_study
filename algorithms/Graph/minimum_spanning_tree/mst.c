#include "mst.h"

#include <limits.h>
#include <stdlib.h>

typedef struct
{
    int from_index;
    int target_index;
    int weight;
} MstEdge;

static Graph *copy_vertices(const Graph *graph)
{
    Graph *copy = create_graph();
    Vertex *vertex = graph->vertices;

    while (vertex != NULL)
    {
        add_vertex(copy, create_vertex(vertex->data));
        vertex = vertex->next;
    }

    return copy;
}

static Vertex **make_vertex_table(Graph *graph)
{
    Vertex **table = calloc((size_t)graph->vertex_count, sizeof(Vertex *));
    Vertex *vertex = graph->vertices;

    if (table == NULL)
    {
        return NULL;
    }

    while (vertex != NULL)
    {
        table[vertex->index] = vertex;
        vertex = vertex->next;
    }

    return table;
}

static void add_undirected_edge(Vertex *from, Vertex *target, int weight)
{
    add_edge(from, create_edge(from, target, weight));
    add_edge(target, create_edge(target, from, weight));
}

static int compare_edge(const void *left, const void *right)
{
    const MstEdge *left_edge = left;
    const MstEdge *right_edge = right;

    if (left_edge->weight < right_edge->weight)
    {
        return -1;
    }

    if (left_edge->weight > right_edge->weight)
    {
        return 1;
    }

    return 0;
}

static int find_root(int *parent, int index)
{
    if (parent[index] != index)
    {
        parent[index] = find_root(parent, parent[index]);
    }

    return parent[index];
}

static void union_sets(int *parent, int *rank, int left, int right)
{
    int left_root = find_root(parent, left);
    int right_root = find_root(parent, right);

    if (left_root == right_root)
    {
        return;
    }

    if (rank[left_root] < rank[right_root])
    {
        parent[left_root] = right_root;
    }
    else if (rank[left_root] > rank[right_root])
    {
        parent[right_root] = left_root;
    }
    else
    {
        parent[right_root] = left_root;
        rank[left_root]++;
    }
}

Graph *mst_prim(const Graph *graph, const Vertex *start_vertex)
{
    int vertex_count;
    int *distance;
    int *parent;
    int *selected;
    Vertex **source_vertices;
    Vertex **tree_vertices;
    Graph *tree;

    if (graph == NULL || start_vertex == NULL || graph->vertex_count == 0)
    {
        return NULL;
    }

    vertex_count = graph->vertex_count;
    distance = malloc(sizeof(int) * (size_t)vertex_count);
    parent = malloc(sizeof(int) * (size_t)vertex_count);
    selected = calloc((size_t)vertex_count, sizeof(int));
    source_vertices = make_vertex_table((Graph *)graph);

    if (distance == NULL || parent == NULL || selected == NULL || source_vertices == NULL)
    {
        free(distance);
        free(parent);
        free(selected);
        free(source_vertices);
        return NULL;
    }

    for (int i = 0; i < vertex_count; i++)
    {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    distance[start_vertex->index] = 0;

    for (int count = 0; count < vertex_count; count++)
    {
        int current_index = -1;
        int minimum = INT_MAX;

        for (int i = 0; i < vertex_count; i++)
        {
            if (!selected[i] && distance[i] < minimum)
            {
                minimum = distance[i];
                current_index = i;
            }
        }

        if (current_index == -1)
        {
            free(distance);
            free(parent);
            free(selected);
            free(source_vertices);
            return NULL;
        }

        selected[current_index] = 1;

        for (Edge *edge = source_vertices[current_index]->adjacenc_list;
             edge != NULL;
             edge = edge->next)
        {
            int target_index = edge->target->index;

            if (!selected[target_index] && edge->weight < distance[target_index])
            {
                distance[target_index] = edge->weight;
                parent[target_index] = current_index;
            }
        }
    }

    tree = copy_vertices(graph);
    tree_vertices = make_vertex_table(tree);

    if (tree_vertices == NULL)
    {
        detroy_graph(tree);
        tree = NULL;
    }
    else
    {
        for (int i = 0; i < vertex_count; i++)
        {
            if (parent[i] != -1)
            {
                add_undirected_edge(tree_vertices[parent[i]], tree_vertices[i], distance[i]);
            }
        }
    }

    free(distance);
    free(parent);
    free(selected);
    free(source_vertices);
    free(tree_vertices);

    return tree;
}

Graph *mst_kruskal(const Graph *graph)
{
    int edge_count = 0;
    int edge_index = 0;
    int selected_count = 0;
    int *parent;
    int *rank;
    MstEdge *edges;
    Vertex **tree_vertices;
    Graph *tree;

    if (graph == NULL || graph->vertex_count == 0)
    {
        return NULL;
    }

    for (Vertex *vertex = graph->vertices; vertex != NULL; vertex = vertex->next)
    {
        for (Edge *edge = vertex->adjacenc_list; edge != NULL; edge = edge->next)
        {
            if (edge->from->index < edge->target->index)
            {
                edge_count++;
            }
        }
    }

    edges = malloc(sizeof(MstEdge) * (size_t)edge_count);
    parent = malloc(sizeof(int) * (size_t)graph->vertex_count);
    rank = calloc((size_t)graph->vertex_count, sizeof(int));

    if (edges == NULL || parent == NULL || rank == NULL)
    {
        free(edges);
        free(parent);
        free(rank);
        return NULL;
    }

    for (Vertex *vertex = graph->vertices; vertex != NULL; vertex = vertex->next)
    {
        for (Edge *edge = vertex->adjacenc_list; edge != NULL; edge = edge->next)
        {
            if (edge->from->index < edge->target->index)
            {
                edges[edge_index++] = (MstEdge){
                    edge->from->index,
                    edge->target->index,
                    edge->weight};
            }
        }
    }

    qsort(edges, (size_t)edge_count, sizeof(MstEdge), compare_edge);

    for (int i = 0; i < graph->vertex_count; i++)
    {
        parent[i] = i;
    }

    tree = copy_vertices(graph);
    tree_vertices = make_vertex_table(tree);

    if (tree_vertices == NULL)
    {
        detroy_graph(tree);
        free(edges);
        free(parent);
        free(rank);
        return NULL;
    }

    for (int i = 0; i < edge_count && selected_count < graph->vertex_count - 1; i++)
    {
        int from_root = find_root(parent, edges[i].from_index);
        int target_root = find_root(parent, edges[i].target_index);

        if (from_root != target_root)
        {
            add_undirected_edge(
                tree_vertices[edges[i].from_index],
                tree_vertices[edges[i].target_index],
                edges[i].weight);

            union_sets(parent, rank, from_root, target_root);
            selected_count++;
        }
    }

    if (selected_count != graph->vertex_count - 1)
    {
        detroy_graph(tree);
        tree = NULL;
    }

    free(edges);
    free(parent);
    free(rank);
    free(tree_vertices);

    return tree;
}

int mst_total_weight(const Graph *tree)
{
    int total_weight = 0;

    if (tree == NULL)
    {
        return 0;
    }

    for (Vertex *vertex = tree->vertices; vertex != NULL; vertex = vertex->next)
    {
        for (Edge *edge = vertex->adjacenc_list; edge != NULL; edge = edge->next)
        {
            if (edge->from->index < edge->target->index)
            {
                total_weight += edge->weight;
            }
        }
    }

    return total_weight;
}

void mst_print(const Graph *tree)
{
    if (tree == NULL)
    {
        printf("MST를 만들 수 없습니다.\n");
        return;
    }

    for (Vertex *vertex = tree->vertices; vertex != NULL; vertex = vertex->next)
    {
        for (Edge *edge = vertex->adjacenc_list; edge != NULL; edge = edge->next)
        {
            if (edge->from->index < edge->target->index)
            {
                printf("%c - %c (%d)\n",
                       edge->from->data,
                       edge->target->data,
                       edge->weight);
            }
        }
    }

    printf("total weight: %d\n", mst_total_weight(tree));
}
