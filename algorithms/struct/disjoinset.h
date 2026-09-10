#ifndef DISJOINSET_H

#define DISJOINSET_H

#include <stdio.h>
#include <stdlib.h>

typedef struct DisjoinSet
{
    struct DisjoinSet *parent;
    void *data;
} DisjoinSet;

void ds_union_set(DisjoinSet *set1, DisjoinSet *set2);
DisjoinSet *ds_find_set(DisjoinSet *set);
DisjoinSet *ds_make_set(void *new_data);
void ds_disjoin_set(DisjoinSet *set);
#endif