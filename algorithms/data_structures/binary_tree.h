#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct SBTNode
{
    SBTNode *left;
    SBTNode *right;
    ElementType data;
} SBTNode;

SBTNode *sbt_create_node(ElementType new_data);

void sbt_destroy_node(SBTNode *node);

void sbt_preorder_print_tree(SBTNode *node);

// 중위

void sbt_inorder_print_tree(SBTNode *node);

// 후위

void sbt_postorder_print_tree(SBTNode *node);

// 이

void sbt_destroy_tree(SBTNode *node);

#endif