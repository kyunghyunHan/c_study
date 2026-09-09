#include "expression_tree.h"

ETNode *et_create_node(ElementType new_data)
{
    ETNode *new_node = (ETNode *)malloc(sizeof(ETNode));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = new_data;

    return new_node;
}
void et_destroy_node(ETNode *node)
{
    free(node);
}
void et_destroy_tree(ETNode *root)
{
    if (root == NULL)
    {
        return;
    }
    et_destroy_tree(root->left);
    et_destroy_tree(root->right);
    et_destroy_node(root);
}

void et_preorder_print_tree(ETNode *node)
{
    if (node == NULL)
    {
        return;
    }
    printf(" %c", node->data);
    et_preorder_print_tree(node->left);
    et_preorder_print_tree(node->right);
}
void et_inorder_print_tree(ETNode *node)
{
    if (node == NULL)
    {
        return;
    }
    printf("(");
    et_inorder_print_tree(node->left);
    printf(" %c", node->data);
    et_inorder_print_tree(node->right);
    printf(")");
}
void et_postorder_print_tree(ETNode *node)
{
    if (node == NULL)
    {
        return;
    }
    et_postorder_print_tree(node->left);
    et_postorder_print_tree(node->right);
    printf(" %c", node->data);
}
void et_build_expression_tree(char *post_fix_expression, ETNode **node)
{
    int len = strlen(post_fix_expression);
    char token = post_fix_expression[len - 1];
    post_fix_expression[len - 1] = '\0';

    switch (token)
    {
    case '+':
    case '-':
    case '*':
    case '/':
        (*node) = et_create_node(token);
        et_build_expression_tree(post_fix_expression, &(*node)->right);
        et_build_expression_tree(post_fix_expression, &(*node)->left);
        break;

    default:
        (*node) = et_create_node(token);
        break;
    }
}
double et_evaluate(ETNode *tree)
{
    char temp[2];
    double left = 0;
    double right = 0;
    double result = 0;

    if (tree == NULL)
    {
        return 0;
    }

    switch (tree->data)
    {
    case '+':
    case '-':
    case '*':
    case '/':
        left = et_evaluate(tree->left);
        right = et_evaluate(tree->right);

        if (tree->data == '+')
        {
            result = left + right;
        }
        else if (tree->data == '-')
        {
            result = left - right;
        }
        else if (tree->data == '*')
        {
            result = left * right;
        }
        else
        {
            result = left / right;
        }
        break;

    default:
        memset(temp, 0, sizeof(temp));
        temp[0] = tree->data;
        result = atof(temp);
        break;
    }

    return result;
}

int main(void)
{

    ETNode *root = NULL;

    char post_fix_expression[20] = "71*52-/";
    et_build_expression_tree(post_fix_expression, &root);

    printf("preorder ... \n");
    et_preorder_print_tree(root);
    printf("\n\n");

    printf("Inorder...\n");
    et_inorder_print_tree(root);
    printf("\n\n");

    printf("Postorder...\n");
    et_postorder_print_tree(root);
    printf("\n\n");

    printf("Evaluation Result : %f \n", et_evaluate(root));

    et_destroy_tree(root);
    return 0;
}