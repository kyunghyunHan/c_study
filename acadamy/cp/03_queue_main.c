#include "03_queue.h"

int main(void)
{
    Queue *queue = NULL;

    int s, n, r, c;
    int count = 0;
    char cmd;

    (void)freopen("data.txt", "r", stdin);
    if (scanf("%d %d", &s, &n) != 2)
        return 1;

    queue = init_queue(s);
    if (queue == NULL)
        return 1;

    while (count < n && scanf(" %c", &cmd) == 1)
    {
        if (cmd == 'P')
        {
            if (scanf("%d %d", &r, &c) != 2)
                break;

            enqueue(queue, r, c);
            count++;
        }
        else if (cmd == 'D')
        {
            dequeue(queue);
        }
    }
    print_q(queue);
    destroy_queue(queue);

    return 0;
}
