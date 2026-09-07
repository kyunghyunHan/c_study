#include <stdio.h>
#include <stdlib.h>

typedef int element_type;

typedef struct tagNode
{
    element_type data;
} Node;

typedef struct tagArrayStack
{
    int capacity;
    int top;
    Node *nodes;
} ArrayStack;

void as_create_stack(ArrayStack **stack, int capacity)
{
    // 스택을 자유 저장소에 생성
    *stack = malloc(sizeof(ArrayStack));

    // 입력된 capacity만큼 노드를 자유저장소에 생성
    (*stack)->nodes = malloc(sizeof(Node) * capacity);

    // capacity 및 top 초기화
    (*stack)->capacity = capacity;
    (*stack)->top = -1;
}

void as_destroy_stack(ArrayStack *stack)
{
    // node를 자유 저장소에서 해제
    free(stack->nodes);

    // 스택을 자유 저장소에서 해제
    free(stack);
}

void as_push(ArrayStack *stack, element_type data)
{
    stack->top++;
    stack->nodes[stack->top].data = data;
}

// 최상위 노드의 인덱스에 있던 값을 반환한다.
element_type as_pop(ArrayStack *stack)
{
    int position = stack->top--;
    return stack->nodes[position].data;
}

int as_get_size(const ArrayStack *stack)
{
    return stack->top + 1;
}

element_type as_top(const ArrayStack *stack)
{
    return stack->nodes[stack->top].data;
}

int as_is_empty(const ArrayStack *stack)
{
    return stack->top == -1;
}

int main(void)
{
    int i = 0;
    ArrayStack *stack = NULL;

    as_create_stack(&stack, 10);

    as_push(stack, 3);
    as_push(stack, 37);
    as_push(stack, 11);
    as_push(stack, 12);

    printf("capacity: %d, size: %d, top: %d\n\n",
           stack->capacity, as_get_size(stack), as_top(stack));

    for (i = 0; i < 4; i++)
    {
        if (as_is_empty(stack))
            break;

        printf("popped: %d, ", as_pop(stack));

        if (!as_is_empty(stack))
            printf("current top: %d\n", as_top(stack));
        else
            printf("stack is empty.\n");
    }

    as_destroy_stack(stack);

    return 0;
}
