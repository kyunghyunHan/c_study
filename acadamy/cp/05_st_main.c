#include "05_st.h"
#include <stdio.h>

void preorder(const Node *node)
{
    if (node == NULL)
    {
        return;
    }

    printf("%c ", node->data);
    preorder(node->left);
    preorder(node->right);
}

void inorder(const Node *node)
{
    if (node == NULL)
    {
        return;
    }

    inorder(node->left);
    printf("%c ", node->data);
    inorder(node->right);
}

void postorder(const Node *node)
{
    if (node == NULL)
    {
        return;
    }

    postorder(node->left);
    postorder(node->right);
    printf("%c ", node->data);
}

int main(void)
{
    Node A, B, C;
    Node D = {'1', NULL, NULL};
    Node E = {'2', NULL, NULL};
    Node F = {'7', NULL, NULL};
    Node G = {'8', NULL, NULL};
    Node *root = &A;

    A = (Node){'+', &B, &C};
    B = (Node){'*', &D, &E};
    C = (Node){'-', &F, &G};

    

    printf("Preorder : ");
    preorder(&A);
    printf("\n");

    printf("Inorder  : ");
    inorder(&A);
    printf("\n");

    printf("Postorder: ");
    postorder(&A);
    printf("\n");

    return 0;
}
