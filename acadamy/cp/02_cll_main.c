#include "02_cll.h"

int main(void)
{
    Node *head = NULL;
    init(&head);

    data_t data = {0, 0};
    int n;
    (void)freopen("data.txt", "r", stdin);
    (void)scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        Node *new_node = NULL;
        (void)scanf("%d %d", &data.id, &data.score);
        new_node = create_node(data);
        if (new_node == NULL)
        {
            destroy_dll(&head);
            head = NULL;
            exit(0);
        }
        append_node(&head, new_node);
    }
    print_node(head);

    return 0;
}
