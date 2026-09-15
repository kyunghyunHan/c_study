#include "rbt.h"

RbtNode *nil;

int main(void)
{
    RbtNode *tree = NULL;
    RbtNode *node = NULL;

    nil = rbt_create_node(0);
    nil->color = BLACK;

    while (1)
    {
        int cmd = 0;
        int param = 0;
        char buffer[10];

        printf("Enter command number :\n");
        printf("(1) Create a node, (2) Remove a node, (3) Search a Node\n");
        printf("(4) Display Tree (5) quit\n");
        printf("command number:");

        fgets(buffer, sizeof(buffer) - 1, stdin);
        sscanf(buffer, "%d", &cmd);

        if (cmd < 1 || cmd > 5)
        {
            printf("Invalid command number.\n");
            continue;
        }
        else if (cmd == 4)
        {
            rbt_print_tree(tree, 0, 0);
            printf("\n");
            continue;
        }
        else if (cmd == 5)
        {
            break;
        }

        printf("Enter parameter (1~200) :\n");

        fgets(buffer, sizeof(buffer) - 1, stdin);
        sscanf(buffer, "%d", &param);

        if (param < 1 || param > 200)
        {
            printf("Invalid parameter.%d\n", param);
            continue;
        }

        switch (cmd)
        {
        case 1:
            rbt_insert_node(&tree, rbt_create_node(param));
            break;

        case 2:
            node = rbt_remove_node(&tree, param);

            if (node == NULL)
            {
                printf("Not found node to delete:%d\n", param);
            }
            else
            {
                rbt_destroy_node(node);
            }

            break;

        case 3:
            node = rbt_search_node(tree, param);

            if (node == NULL)
            {
                printf("Not found node:%d\n", param);
            }
            else
            {
                printf("Found Node: %d(Color:%s)\n",
                       node->data,
                       (node->color == RED) ? "RED" : "BLACK");
            }

            break;
        }

        printf("\n");
    }

    if (tree != NULL)
    {
        rbt_destroy_tree(tree);
    }

    rbt_destroy_node(nil);

    return 0;
}