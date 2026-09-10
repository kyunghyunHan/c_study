#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef char ElementType;

typedef struct LcrNode
{
    struct LcrNode *left_child;
    struct LcrNode *right_sibing;

    ElementType data;

} LcrNode;


LcrNode *lcrs_create_node(ElementType new_data);

void lcrs_destroy_node(LcrNode *node);
void lcrs_add_child_node(LcrNode *parent, LcrNode *child);
void lcrs_print_tree(LcrNode *node, int depth);

#endif