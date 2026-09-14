#include "02_dll.h"

int main(void)
{
    Node *head = NULL;
    Node *tail = NULL;
    init_HT(&head, &tail);

    data_t data = {0};
    int n;
    (void)freopen("data.txt", "r", stdin);
    (void)scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        Node *new_node = NULL;
        (void)scanf("%d %d", &data.id, &data.score);
        new_node = create_node(&data);
        printf("%d %d\n", new_node->data.id, new_node->data.score);
        if (new_node == NULL)
        {
            // Destroy_DLL(head);
            head = NULL;
            exit(0);
        }
        // Append_Node(head, newnode);
    }
    // Print_Node(head->next);

    return 0;
}