#ifndef EXPRESSION_TREE_H

#define EXPRESSION_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char ElementType;
typedef struct ETNode
{
    struct ETNode *left;
    struct ETNode *right;
    ElementType data;
} ETNode;

ETNode *et_create_node(ElementType new_data);
void et_destroy_node(ETNode *node);
void et_destroy_tree(ETNode *root);

void et_preorder_print_tree(ETNode *node);
void et_inorder_print_tree(ETNode *node);
void et_postorder_print_tree(ETNode *node);
void et_build_expression_tree(char *post_fix_expression, ETNode **node);
double et_evaluate(ETNode *tree);

#endif
