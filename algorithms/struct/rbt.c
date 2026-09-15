#include "rbt.h"
#include <string.h>
/* */
extern RbtNode *nil;

RbtNode *rbt_create_node(ElementType new_data)
{
    RbtNode *new_node = (RbtNode *)malloc(sizeof(RbtNode));
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = new_data;
    new_node->color = BLACK;

    return new_node;
}

void rbt_destroy_tree(RbtNode *tree)
{
}

void rbt_detroy_tree(RbtNode *tree)
{
    if (tree->right != nil)
    {
        rbt_destroy_tree(tree->right);
    }

    if (tree->left != nil)
    {
        rbt_destroy_tree(tree->left);
    }

    tree->left = nil;
    tree->right = nil;
}