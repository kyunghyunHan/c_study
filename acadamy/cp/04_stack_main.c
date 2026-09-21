#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if 01

typedef struct Stack
{
    int *data;
    size_t size;
    size_t top;
} Stack;

// 메모리 할당및 해지 한번
Stack *init_stack(size_t size)
{
    Stack *stack = calloc(1, sizeof(*stack) + size * sizeof(*stack->data));
    if (stack != NULL)
    {
        stack->data = (int *)(stack + 1);
        stack->size = size;
    }

    return stack;
}

int push(Stack *stack, int data)
{
    if (stack->top >= stack->size)
    {
        printf("Overflow\n");
        return -1;
    }
    stack->data[stack->top++] = data;
    printf("Push: %d\n", data);
    return 0;
}

int pop(Stack *stack)
{
    if (stack->top <= 0)
    {
        printf("Underflow\n");
        return -1;
    }
    int data = stack->data[--(*stack).top];
    printf("Pop: %d\n", data);
    return data;
}

int main(void)
{
    Stack *stack = NULL;
    int size, cmd_cnt, data;
    char cmd[5] = {0};
    (void)freopen("sdata.txt", "r", stdin);
    if (scanf("%d %d", &size, &cmd_cnt) != 2 || size <= 0 || cmd_cnt < 0)
    {
        return 1;
    }

    stack = init_stack((size_t)size);
    if (stack == NULL)
    {
        return 1;
    }

    for (int i = 0; i < cmd_cnt; ++i)
    {
        (void)scanf("%4s", cmd);
        if (!strcmp(cmd, "push"))
        {
            (void)scanf("%d", &data);
            push(stack, data);
        }
        else
        {
            pop(stack);
        }
    }

    printf("Stack:");
    int stack_size = (*stack).size;

    while (size)
    {
        printf("%d\n", (*stack).data[--size]);
    }
    // for (size_t i = 0; i < stack->top; ++i)
    // {
    //     printf(" %d", stack->data[i]);
    // }
    printf("\n");

    free(stack);

    return 0;
}
#endif
