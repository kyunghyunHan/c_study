#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int ElementType;

/*
모든 노드는 빨간색 또는 검은색
루트 노드는 검은색
NIL(잎) 노드는 검은색
빨간색 노드의 자식은 모두 검은색
루트부터 모든 NIL까지의 검은색 노드 수는 동일
*/

typedef struct RbtNode
{
    struct RbtNode *parent;
    struct RbtNode *left;
    struct RbtNode *right;

    enum
    {
        RED,
        BLACK
    } color;

    ElementType data;

} RbtNode;

void rbt_destroy_tree(RbtNode *tree);

RbtNode *rbt_create_node(ElementType new_data);
void rbt_destroy_node(RbtNode *node);

RbtNode *rbt_search_node(RbtNode *tree, ElementType target);
RbtNode *rbt_search_min_node(RbtNode *tree);

void rbt_insert_node(RbtNode **tree, RbtNode *new_node);
void rbt_insert_node_helper(RbtNode **tree, RbtNode *new_node);

RbtNode *rbt_remove_node(RbtNode **root, ElementType target);

void rbt_rebuild_after_insert(RbtNode **tree, RbtNode *new_node);
void rbt_rebuild_after_remove(RbtNode **root, RbtNode *x);

void rbt_print_tree(RbtNode *node, int depth, int black_count);

void rbt_rotate_left(RbtNode **root, RbtNode *parent);
void rbt_rotate_right(RbtNode **root, RbtNode *parent);

#endif