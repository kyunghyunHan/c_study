#include "rbt.h"
#include <string.h>
/*

1        2
p head   p
n head


*/
extern RbtNode *nil;

RbtNode *rbt_create_node(ElementType new_data)
{
    RbtNode *new_node = (RbtNode *)malloc(sizeof(RbtNode));
    if (new_node == NULL)
    {
        return NULL;
    }

    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = new_data;
    new_node->color = BLACK;

    return new_node;
}

void rbt_destroy_node(RbtNode *node)
{
    free(node);
}

void rbt_destroy_tree(RbtNode *tree)
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

    rbt_destroy_node(tree);
}

RbtNode *rbt_search_node(RbtNode *tree, ElementType target)
{
    if (tree == NULL || tree == nil)
    {
        return NULL;
    }
    if (tree->data > target)
    {
        return rbt_search_node(tree->left, target);
    }
    else if (tree->data < target)
    {
        return rbt_search_node(tree->right, target);
    }
    else
    {
        return tree;
    }
}

RbtNode *rbt_search_min_node(RbtNode *tree)
{
    if (tree == NULL || tree == nil)
    {
        return nil;
    }

    if (tree->left == nil)
    {
        return tree;
    }
    else
    {
        return rbt_search_min_node(tree->left);
    }
}

void rbt_insert_node(RbtNode **tree, RbtNode *new_node)
{
    if (tree == NULL || new_node == NULL)
    {
        return;
    }

    if (*tree != NULL && rbt_search_node(*tree, new_node->data) != NULL)
    {
        rbt_destroy_node(new_node);
        return;
    }

    /* The sentinel's children are also black sentinel leaves. */
    nil->left = nil;
    nil->right = nil;

    rbt_insert_node_helper(tree, new_node);

    new_node->color = RED;
    new_node->left = nil;
    new_node->right = nil;

    rbt_rebuild_after_insert(tree, new_node);
}

void rbt_insert_node_helper(RbtNode **tree, RbtNode *new_node)
{
    if ((*tree) == NULL)
    {
        (*tree) = new_node;
        new_node->parent = NULL;
        return;
    }

    if ((*tree)->data < new_node->data)
    {
        if ((*tree)->right == nil)
        {
            (*tree)->right = new_node;
            new_node->parent = (*tree);
        }
        else
        {
            rbt_insert_node_helper(&(*tree)->right, new_node);
        }
    }
    else if ((*tree)->data > new_node->data)
    {
        if ((*tree)->left == nil)
        {
            (*tree)->left = new_node;
            new_node->parent = (*tree);
        }
        else
        {
            rbt_insert_node_helper(&(*tree)->left, new_node);
        }
    }
}

void rbt_rotate_right(RbtNode **root, RbtNode *parent)
{
    RbtNode *left_child = parent->left;
    parent->left = left_child->right;

    if (left_child->right != nil)
    {
        left_child->right->parent = parent;
    }

    left_child->parent = parent->parent;

    if (parent->parent == NULL)
    {
        (*root) = left_child;
    }
    else
    {
        if (parent == parent->parent->left)
        {
            parent->parent->left = left_child;
        }
        else
        {
            parent->parent->right = left_child;
        }
    }

    left_child->right = parent;
    parent->parent = left_child;
}
void rbt_rotate_left(RbtNode **root, RbtNode *parent)
{
    RbtNode *right_child = parent->right;
    parent->right = right_child->left;

    if (right_child->left != nil)
    {
        right_child->left->parent = parent;
    }
    right_child->parent = parent->parent;

    if (parent->parent == NULL)
    {
        (*root) = right_child;
    }
    else
    {
        if (parent == parent->parent->left)
        {
            parent->parent->left = right_child;
        }
        else
        {
            parent->parent->right = right_child;
        }
    }

    right_child->left = parent;
    parent->parent = right_child;
}

void rbt_rebuild_after_insert(RbtNode **root, RbtNode *x)
{
    while (x != (*root) && x->parent->color == RED)
    {
        if (x->parent == x->parent->parent->left)
        {
            RbtNode *uncle = x->parent->parent->right;

            if (uncle->color == RED)
            {
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x->parent->parent->color = RED;

                x = x->parent->parent;
            }
            else
            {
                if (x == x->parent->right)
                {
                    x = x->parent;
                    rbt_rotate_left(root, x);
                }

                x->parent->color = BLACK;
                x->parent->parent->color = RED;

                rbt_rotate_right(root, x->parent->parent);
            }
        }
        else
        {
            RbtNode *uncle = x->parent->parent->left;

            if (uncle->color == RED)
            {
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x->parent->parent->color = RED;

                x = x->parent->parent;
            }
            else
            {
                if (x == x->parent->left)
                {
                    x = x->parent;
                    rbt_rotate_right(root, x);
                }

                x->parent->color = BLACK;
                x->parent->parent->color = RED;

                rbt_rotate_left(root, x->parent->parent);
            }
        }
    }

    (*root)->color = BLACK;
}

static void rbt_transplant(RbtNode **root, RbtNode *old_node, RbtNode *new_node)
{
    if (old_node->parent == NULL)
    {
        *root = new_node;
    }
    else if (old_node == old_node->parent->left)
    {
        old_node->parent->left = new_node;
    }
    else
    {
        old_node->parent->right = new_node;
    }

    new_node->parent = old_node->parent;
}

RbtNode *rbt_remove_node(RbtNode **root, ElementType target)
{
    if (root == NULL || *root == NULL || *root == nil)
    {
        return NULL;
    }

    RbtNode *removed = rbt_search_node(*root, target);
    if (removed == NULL)
    {
        return NULL;
    }

    RbtNode *replacement = removed;
    RbtNode *fix_node;
    int original_color = replacement->color;

    if (removed->left == nil)
    {
        fix_node = removed->right;
        rbt_transplant(root, removed, removed->right);
    }
    else if (removed->right == nil)
    {
        fix_node = removed->left;
        rbt_transplant(root, removed, removed->left);
    }
    else
    {
        replacement = rbt_search_min_node(removed->right);
        original_color = replacement->color;
        fix_node = replacement->right;

        if (replacement->parent == removed)
        {
            fix_node->parent = replacement;
        }
        else
        {
            rbt_transplant(root, replacement, replacement->right);
            replacement->right = removed->right;
            replacement->right->parent = replacement;
        }

        rbt_transplant(root, removed, replacement);
        replacement->left = removed->left;
        replacement->left->parent = replacement;
        replacement->color = removed->color;
    }

    if (original_color == BLACK)
    {
        rbt_rebuild_after_remove(root, fix_node);
    }

    if (*root == nil)
    {
        *root = NULL;
    }
    nil->parent = NULL;

    removed->parent = NULL;
    removed->left = NULL;
    removed->right = NULL;
    return removed;
}

void rbt_rebuild_after_remove(RbtNode **root, RbtNode *x)
{
    RbtNode *sibling = NULL;

    while (x != *root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            sibling = x->parent->right;

            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                x->parent->color = RED;

                rbt_rotate_left(root, x->parent);

                sibling = x->parent->right;
            }

            if (sibling->left->color == BLACK &&
                sibling->right->color == BLACK)
            {
                sibling->color = RED;
                x = x->parent;
            }
            else
            {
                if (sibling->right->color == BLACK)
                {
                    sibling->left->color = BLACK;
                    sibling->color = RED;

                    rbt_rotate_right(root, sibling);

                    sibling = x->parent->right;
                }

                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                sibling->right->color = BLACK;

                rbt_rotate_left(root, x->parent);

                x = (*root);
            }
        }
        else
        {
            sibling = x->parent->left;

            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                x->parent->color = RED;

                rbt_rotate_right(root, x->parent);

                sibling = x->parent->left;
            }

            if (sibling->right->color == BLACK &&
                sibling->left->color == BLACK)
            {
                sibling->color = RED;
                x = x->parent;
            }
            else
            {
                if (sibling->left->color == BLACK)
                {
                    sibling->right->color = BLACK;
                    sibling->color = RED;

                    rbt_rotate_left(root, sibling);

                    sibling = x->parent->left;
                }

                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                sibling->left->color = BLACK;

                rbt_rotate_right(root, x->parent);

                x = (*root);
            }
        }
    }

    x->color = BLACK;
}
void rbt_print_tree(RbtNode *node, int depth, int black_count)
{
    int i = 0;
    char c = 'X';
    int v = -1;
    char cnt[100];

    if (node == NULL || node == nil)
    {
        return;
    }

    if (node->color == BLACK)
    {
        black_count++;
    }

    if (node->parent != NULL)
    {
        v = node->parent->data;

        if (node->parent->left == node)
        {
            c = 'L';
        }
        else
        {
            c = 'R';
        }
    }

    if (node->left == nil && node->right == nil)
    {
        snprintf(cnt, sizeof(cnt), "------- %d", black_count);
    }
    else
    {
        cnt[0] = '\0';
    }

    for (i = 0; i < depth; i++)
    {
        printf(" ");
    }

    printf("%d %s [%c,%d] %s\n",
           node->data,
           (node->color == RED) ? "RED" : "BLACK",
           c,
           v,
           cnt);

    rbt_print_tree(node->left, depth + 1, black_count);
    rbt_print_tree(node->right, depth + 1, black_count);
}
