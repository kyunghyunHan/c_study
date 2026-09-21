#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if 01
int *stack = 0;
int top = 0;

void push(int *stack, int data, int size)
{
    if (top == size)
    {
        printf("Overflow\n");
        return;
    }
    stack[top++] = data;
    printf("Push: %d\n", data);
}

int pop(void)
{
    if (top == 0)
    {
        printf("Underflow\n");
        return -1;
    }
    int data = stack[--top];
    printf("Pop: %d\n", data);
    return data;
}
int main(void)
{
    int size, cmd_cnt, data;
    char cmd[5] = {0};
    (void)freopen("sdata.txt", "r", stdin);
    (void)scanf("%d %d", &size, &cmd_cnt);
    stack = (int *)malloc(sizeof(int) * size);
    if (stack == NULL)
    {
        return 1;
    }

    for (int i = 0; i < cmd_cnt; ++i)
    {
        (void)scanf("%s", cmd);
        if (!strcmp(cmd, "push"))
        {
            (void)scanf("%d", &data);
            push(stack, data, size);
        }
        else
        {
            pop();
        }
    }

    printf("Stack:");
    for (int i = 0; i < top; ++i)
    {
        printf(" %d", stack[i]);
    }
    printf("\n");

    free(stack);

    return 0;
}
#endif
