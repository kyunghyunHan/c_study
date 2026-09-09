#include "tree.h"
/*
tree

parent  , children  ,sibing
length , depth

*/

LcrNode *lcrs_create_node(ElementType new_data)
{
    LcrNode *new_node = (LcrNode *)malloc(sizeof(LcrNode));
    new_node->left_child = NULL;
    new_node->right_sibing = NULL;
    new_node = new_data;

    return new_node;
}

void lcrs_destroy_node(LcrNode *node)
{
    free(node);
}