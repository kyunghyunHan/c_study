#include "binary_tree.h"
/*
이진 트리
노드  최대 차수 2
모든 이진 트리 노드의 자식 노드 수는 0, 1, 2

포화 이진트리 = 왼쪽부터 차곡차곡

전위순위 , 중위 순위 , 후위순위

*/

SBTNode *sbt_create_node(ElementType new_data)
{
    SBTNode *new_node = (SBTNode *)malloc(sizeof(SBTNode));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = new_data;

    return new_node;
}

void sbt_destroy_node(SBTNode *node)
{
    free(node);
}
// 전위
void sbt_preorder_print_tree(SBTNode *node)
{
    if (node == NULL)
    {
        return;
    }

    // 뿌리 노드출력
    printf(" %c", node->data);

    // 왼쪽 하위 트리 출력
    sbt_preorder_print_tree(node->left);

    // 오른쪾 하위 트리 출략
    sbt_preorder_print_tree(node->right);
}

// 중위

void sbt_inorder_print_tree(SBTNode *node)
{
    if (node == NULL)
    {
        return;
    }

    // 왼쪽 하위 트 출략
    sbt_inorder_print_tree(node->left);

    // 뿌리 논드 출력
    printf(" %c", node->data);

    // 오른쪾 하위 트리 출력
    sbt_inorder_print_tree(node->right);
}

// 후위

void sbt_postorder_print_tree(SBTNode *node)
{
    if (node == NULL)
    {
        return;
    }
    sbt_postorder_print_tree(node->left);

    sbt_postorder_print_tree(node->right);

    printf(" %c", node->data);
}

// 이

void sbt_destroy_tree(SBTNode *node)
{
    if (node == NULL)
    {
        return;
    }

    sbt_destroy_tree(node->left);
    sbt_destroy_tree(node->right);

    sbt_destroy_node(node);
}

int main(void)
{
    SBTNode *a = sbt_create_node('A');
    SBTNode *b = sbt_create_node('B');
    SBTNode *c = sbt_create_node('C');
    SBTNode *d = sbt_create_node('D');
    SBTNode *e = sbt_create_node('E');
    SBTNode *f = sbt_create_node('F');
    SBTNode *g = sbt_create_node('G');

    a->left = b;
    b->left = c;
    b->right = d;

    a->right = e;
    e->left = f;
    e->right = g;

    // 트리 출력

    printf("Preorder ...\n");
    sbt_preorder_print_tree(a);
    printf("\n\n");

    printf("Inorder...\n");
    sbt_inorder_print_tree(a);
    printf("\n\n");

    printf("Postorder ...\n");
    sbt_postorder_print_tree(a);
    printf("\n\n");

    return 0;
}