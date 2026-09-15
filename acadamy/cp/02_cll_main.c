#include "02_cll.h"

int main(void)
{
    char initial[100001];
    int command_count;

    if (scanf("%100000s", initial) != 1 ||
        scanf("%d", &command_count) != 1)
    {
        return EXIT_FAILURE;
    }

    Node *head = NULL;
    init(&head);
    if (head == NULL)
        return EXIT_FAILURE;

    /* cursor points to the node immediately to the left of the cursor. */
    Node *cursor = head;
    for (size_t i = 0; initial[i] != '\0'; i++)
    {
        Node *new_node = create_node((data_t){.ch = initial[i]});
        if (new_node == NULL)
        {
            destroy_list(&head);
            return EXIT_FAILURE;
        }
        append_node(&head, new_node);
        cursor = new_node;
    }

    for (int i = 0; i < command_count; i++)
    {
        char command;
        if (scanf(" %c", &command) != 1)
            break;

        if (command == 'L')
        {
            if (cursor != head)
                cursor = cursor->prev;
        }
        else if (command == 'D')
        {
            if (cursor->next != head)
                cursor = cursor->next;
        }
        else if (command == 'B')
        {
            if (cursor != head)
            {
                Node *previous = cursor->prev;
                remove_node(cursor);
                cursor = previous;
            }
        }
        else if (command == 'P')
        {
            char ch;
            if (scanf(" %c", &ch) != 1)
                break;

            Node *new_node = create_node((data_t){.ch = ch});
            if (new_node == NULL)
            {
                destroy_list(&head);
                return EXIT_FAILURE;
            }
            insert_after(cursor, new_node);
            cursor = new_node;
        }
    }

    print_node(head);
    destroy_list(&head);
    return EXIT_SUCCESS;
}
