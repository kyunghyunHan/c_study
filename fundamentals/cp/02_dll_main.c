#include "02_dll.h"

int main(void)
{
    Node *head = NULL;
    Node *tail = NULL;
    init_HT(&head, &tail);

    data_t data = {0};
    FILE *input = fopen("data.txt", "r");

    if (input == NULL)
    {
        input = stdin;
    }

    while (fscanf(input, "%d %d", &data.id, &data.score) == 2)
    {
        Node *new_node = NULL;

        new_node = create_node(&data);
        if (new_node == NULL)
        {
            // Destroy_DLL(head);
            head = NULL;
            exit(0);
        }
        append_node(&head, new_node);
    }
    print_node(head);

    return 0;
}
