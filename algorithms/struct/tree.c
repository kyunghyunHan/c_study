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
    new_node->data = new_data;

    return new_node;
}

void lcrs_destroy_node(LcrNode *node)
{
    free(node);
}
// node 에 자식 노드 연결
void lcrs_add_child_node(LcrNode *parent, LcrNode *child)
{
    if (parent->left_child == NULL)
    {
        parent->left_child = child;
    }
    else
    {
        LcrNode *temp_node = parent->left_child;
        while (temp_node->right_sibing != NULL)
        {
            temp_node = temp_node->right_sibing;
        }
        temp_node->right_sibing = child;
    }
}

void lcrs_print_tree(LcrNode *node, int depth)
{
    // 들여쓰기
    int i = 0;
    for (int i = 0; i < depth - 1; i++)
    {
        printf("    ");
    }
    if (depth > 0)
    {
        printf("+--");
    }
    // 노드 데이터 출력
    printf("%c\n", node->data);

    if (node->left_child != NULL)
    {
        lcrs_print_tree(node->left_child, depth + 1);
    }
    if (node->right_sibing != NULL)
    {
        lcrs_print_tree(node->right_sibing, depth);
    }
}

int main(void)
{
    // 노드 생성
    LcrNode *root = lcrs_create_node('A');
    LcrNode *b = lcrs_create_node('B');
    LcrNode *c = lcrs_create_node('C');
    LcrNode *d = lcrs_create_node('D');
    LcrNode *e = lcrs_create_node('E');
    LcrNode *f = lcrs_create_node('F');
    LcrNode *g = lcrs_create_node('G');
    LcrNode *h = lcrs_create_node('H');
    LcrNode *i = lcrs_create_node('I');
    LcrNode *j = lcrs_create_node('J');
    LcrNode *k = lcrs_create_node('K');

    // 트리에 노드 추가
    lcrs_add_child_node(root, b);
    lcrs_add_child_node(b, c);
    lcrs_add_child_node(b, d);
    lcrs_add_child_node(d, e);
    lcrs_add_child_node(d, f);

    lcrs_add_child_node(root, g);
    lcrs_add_child_node(g, h);

    lcrs_add_child_node(root, i);
    lcrs_add_child_node(i, j);
    lcrs_add_child_node(j, k);

    lcrs_print_tree(root, 0);
    lcrs_destroy_node(root);
    return 0;
}

/*
특정 레벨의 모든 노드를 출력하는 lcrs_print_nodes_at_lavel
*/