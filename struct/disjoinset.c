#include "disjoinset.h"

void ds_union_set(DisjoinSet *set1, DisjoinSet *set2)
{
    set2 = ds_find_set(set2);
    set2->parent = set1;
}
DisjoinSet *ds_find_set(DisjoinSet *set)
{
    while (set->parent != NULL)
    {
        set = set->parent;
    }
    return set;
}
DisjoinSet *ds_make_set(void *new_data)
{
    DisjoinSet *new_node = (DisjoinSet *)malloc(sizeof(DisjoinSet));
    new_node->data = new_data;
    new_node->parent = NULL;

    return new_node;
}
void ds_disjoin_set(DisjoinSet *set)
{
    free(set);
}

int main(void)
{
    int a = 1, b = 2, c = 3, d = 4;
    DisjoinSet *set1 = ds_make_set(&a);
    DisjoinSet *set2 = ds_make_set(&b);
    DisjoinSet *set3 = ds_make_set(&c);
    DisjoinSet *set4 = ds_make_set(&d);

    printf("Set1 == Set2 : %d\n", ds_find_set(set1) == ds_find_set(set2));

    ds_union_set(set1, set3);

    printf("Set1 == Set3 : %d\n", ds_find_set(set1) == ds_find_set(set3));

    ds_union_set(set3, set4);
    printf("Set3 == Set4 : %d\n", ds_find_set(set3) == ds_find_set(set4));

    return 0;
}