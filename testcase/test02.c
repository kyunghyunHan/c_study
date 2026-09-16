/* STack
TOP 하나만 잇으면댐
count
size

*/

#include <stdio.h>
#include <stdlib.h>
typedef struct _Data
{
    int id;
    int score;
} Data;

typedef struct _Node
{
    Data data;
    struct _Node *next_node;
} Node;

typedef struct Stack
{
    Node *top;
    int count;
    int size;

} Stack;

Stack *init(int s)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL)
    {
        return NULL;
    }
    (*stack).top = NULL;
    (*stack).count = 0;
    (*stack).size = s;
    return stack;
}
Node *create_node(Data data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        NULL;
    }
    (*new_node).data = data;
    (*new_node).next_node = NULL;
    return new_node;
}
void push(Stack *stack, Node *new_node)
{
    if (stack == NULL || new_node == NULL)
    {
        return;
    }
    // 아래로감
    (new_node->next_node) = (*stack).top;
    (*stack).top = new_node;
    (*stack).count++;
}
Node *pop(Stack *stack)
{
    if (stack == NULL)
    {
        return NULL;
    }
    Node *target = (*stack).top;
    (*stack).top = (*(*stack).top).next_node;
    (*target).next_node = NULL;
    (*stack).count--;
    return target;
}

void destroy_node(Node *node)
{
    if (node == NULL)
        return;

    free(node);
}
void destroy_stack(Stack *queue)
{
    if (queue == NULL)
        return;

    free(queue);
}
void print_stack(Stack *stack)
{
    if (stack == NULL)
    {
        return;
    }
    int i = 0;
    Node *target = (*stack).top;
    while (i < (*stack).count)
    {
        printf("%d %d\n", (*target).data.id, (*target).data.score);
        target = (*target).next_node;
        i++;
    }
}
int main(void)
{

    int s, n, r, c;
    int count = 0;
    char cmd;

    (void)freopen("data.txt", "r", stdin);
    if (scanf("%d %d", &s, &n) != 2)
        return 1;

    Stack *stack = init(s);

    if (stack == NULL)
        return 1;

    while (count < n && scanf(" %c", &cmd) == 1)
    {
        if (cmd == 'P')
        {
            if (scanf("%d %d", &r, &c) != 2)
                break;
            Node *new_node = create_node((Data){r, c});
            push(stack, new_node);
        }
        else if (cmd == 'D')
        {
            Node *removed = pop(stack);
            destroy_node(removed);
        }
    }
    print_stack(stack);
    destroy_stack(stack);

    return 0;
}