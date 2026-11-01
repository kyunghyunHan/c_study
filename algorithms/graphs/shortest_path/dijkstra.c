#include "dijkstra.h"

#include <limits.h>
#include <stdlib.h>

typedef struct
{
    int vertex_index;
    int distance;
} HeapNode;

typedef struct
{
    HeapNode *nodes;
    int size;
    int capacity;
} MinHeap;

static Vertex **make_vertex_table(const Graph *graph)
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

static int count_edges(const Graph *graph)
{
    int edge_count = 0;

    for (Vertex *vertex = graph->vertices; vertex != NULL; vertex = vertex->next)
    {
        for (Edge *edge = vertex->adjacenc_list; edge != NULL; edge = edge->next)
        {
            if (edge->weight < 0)
            {
                return -1;
            }

            edge_count++;
        }
    }

    return edge_count;
}

static int heap_push(MinHeap *heap, HeapNode new_node)
{
    int child;

    if (heap->size + 1 >= heap->capacity)
    {
        int new_capacity = heap->capacity * 2;
        HeapNode *new_nodes = realloc(
            heap->nodes,
            sizeof(HeapNode) * (size_t)new_capacity);

        if (new_nodes == NULL)
        {
            return 0;
        }

        heap->nodes = new_nodes;
        heap->capacity = new_capacity;
    }

    child = ++heap->size;

    while (child > 1 &&
           heap->nodes[child / 2].distance > new_node.distance)
    {
        heap->nodes[child] = heap->nodes[child / 2];
        child /= 2;
    }

    heap->nodes[child] = new_node;
    return 1;
}

static HeapNode heap_pop(MinHeap *heap)
{
    HeapNode result = heap->nodes[1];
    HeapNode last = heap->nodes[heap->size--];
    int parent = 1;

    while (parent * 2 <= heap->size)
    {
        int child = parent * 2;

        if (child + 1 <= heap->size &&
            heap->nodes[child + 1].distance < heap->nodes[child].distance)
        {
            child++;
        }

        if (last.distance <= heap->nodes[child].distance)
        {
            break;
        }

        heap->nodes[parent] = heap->nodes[child];
        parent = child;
    }

    heap->nodes[parent] = last;
    return result;
}

static void print_path(
    Vertex **vertices,
    int vertex_count,
    int start_index,
    int target_index,
    const int *previous)
{
    int *path;
    int path_size = 0;
    int current_index = target_index;

    path = malloc(sizeof(int) * (size_t)vertex_count);

    if (path == NULL)
    {
        return;
    }

    while (current_index != -1)
    {
        path[path_size++] = current_index;

        if (current_index == start_index)
        {
            break;
        }

        current_index = previous[current_index];
    }

    for (int i = path_size - 1; i >= 0; i--)
    {
        printf("%c", vertices[path[i]]->data);

        if (i > 0)
        {
            printf(" -> ");
        }
    }

    free(path);
}

int dijkstra_shortest_path(
    const Graph *graph,
    const Vertex *start_vertex,
    int *distance,
    int *previous)
{
    int edge_count;
    Vertex **vertices;
    MinHeap heap;

    if (graph == NULL || start_vertex == NULL ||
        distance == NULL || previous == NULL ||
        graph->vertex_count == 0)
    {
        return 0;
    }

    edge_count = count_edges(graph);

    if (edge_count < 0)
    {
        return 0;
    }

    vertices = make_vertex_table(graph);
    heap.capacity = edge_count + graph->vertex_count + 2;
    heap.size = 0;
    heap.nodes = malloc(sizeof(HeapNode) * (size_t)heap.capacity);

    if (vertices == NULL || heap.nodes == NULL)
    {
        free(vertices);
        free(heap.nodes);
        return 0;
    }

    for (int i = 0; i < graph->vertex_count; i++)
    {
        distance[i] = INT_MAX;
        previous[i] = -1;
    }

    distance[start_vertex->index] = 0;

    if (!heap_push(&heap, (HeapNode){start_vertex->index, 0}))
    {
        free(vertices);
        free(heap.nodes);
        return 0;
    }

    while (heap.size > 0)
    {
        HeapNode current = heap_pop(&heap);

        if (current.distance != distance[current.vertex_index])
        {
            continue;
        }

        for (Edge *edge = vertices[current.vertex_index]->adjacenc_list;
             edge != NULL;
             edge = edge->next)
        {
            int target_index = edge->target->index;
            long long new_distance =
                (long long)current.distance + edge->weight;

            if (new_distance < distance[target_index])
            {
                distance[target_index] = (int)new_distance;
                previous[target_index] = current.vertex_index;

                if (!heap_push(
                        &heap,
                        (HeapNode){target_index, distance[target_index]}))
                {
                    free(vertices);
                    free(heap.nodes);
                    return 0;
                }
            }
        }
    }

    free(vertices);
    free(heap.nodes);
    return 1;
}

void dijkstra_print_result(
    const Graph *graph,
    const Vertex *start_vertex,
    const int *distance,
    const int *previous)
{
    Vertex **vertices;

    if (graph == NULL || start_vertex == NULL ||
        distance == NULL || previous == NULL)
    {
        return;
    }

    vertices = make_vertex_table(graph);

    if (vertices == NULL)
    {
        return;
    }

    for (int i = 0; i < graph->vertex_count; i++)
    {
        printf("%c -> %c: ", start_vertex->data, vertices[i]->data);

        if (distance[i] == INT_MAX)
        {
            printf("unreachable\n");
            continue;
        }

        printf("distance = %d, path = ", distance[i]);
        print_path(
            vertices,
            graph->vertex_count,
            start_vertex->index,
            i,
            previous);
        printf("\n");
    }

    free(vertices);
}
