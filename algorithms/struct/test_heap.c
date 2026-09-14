#include "heap.h"
int main(void)
{

    Heap *h = heap_create(3);
    Node min_node;

    heap_insert(h, 12);
    heap_insert(h, 87);
    heap_insert(h, 111);
    heap_insert(h, 34);
    heap_insert(h, 16);
    heap_insert(h, 75);
    heap_print_nodes(h);

    heap_delete_min(h, &min_node);
    heap_print_nodes(h);

    heap_delete_min(h, &min_node);
    heap_print_nodes(h);

    heap_delete_min(h, &min_node);
    heap_print_nodes(h);

    heap_delete_min(h, &min_node);
    heap_print_nodes(h);

    heap_delete_min(h, &min_node);
    heap_print_nodes(h);

    heap_delete_min(h, &min_node);
    heap_print_nodes(h);

    heap_delete_min(h, &min_node);
    heap_print_nodes(h);
    return 0;
}