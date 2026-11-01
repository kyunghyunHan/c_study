/*
배열로 구현 스택
비용이큼 구현이 간단

*/

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct tagNode
{
    ElementType data;
} Node;

typedef struct tagArrayStack
{
    int capacity; // 용량
    int top;      // 최상위 노드위치
    Node *nodes;  // 노드 배열
} ArrayStack;

void as_create_stack(ArrayStack **stack, int capacity)
{
    if (stack == NULL || capacity <= 0)
    {
        return;
    }

    *stack = NULL;

    // 스택을 자유 저장소에 생성
    *stack = malloc(sizeof(ArrayStack));
    if (*stack == NULL)
    {
        return;
    }

    // 입력된 capacity만큼 노드를 자유저장소에 생성
    (*stack)->nodes = malloc(sizeof(Node) * capacity);
    if ((*stack)->nodes == NULL)
    {
        free(*stack);
        *stack = NULL;
        return;
    }

    // capacity 및 top 초기화
    (*stack)->capacity = capacity;
    (*stack)->top = -1; // c언어에서 첫번쨰 배열요소를 가라키는 배열요소를 첨가가 0 이기때문에 비어있는 최상의 스택은 이보다 작아야 하기떄문에
}
// 스택제거
void as_destroy_stack(ArrayStack *stack)
{
    if (stack == NULL)
    {
        return;
    }

    // node를 자유 저장소에서 해제
    free(stack->nodes);

    // 스택을 자유 저장소에서 해제
    free(stack);
}
//
void as_push(ArrayStack *stack, ElementType data)
{
    if (stack == NULL || stack->top + 1 >= stack->capacity)
    {
        return;
    }

    stack->top++;
    stack->nodes[stack->top].data = data;
}

// 최상위 노드의 인덱스에 있던 값을 반환한다.
ElementType as_pop(ArrayStack *stack)
{
    if (stack == NULL || stack->top == -1)
    {
        return 0;
    }

    int position = stack->top--;
    return stack->nodes[position].data;
}

int as_get_size(const ArrayStack *stack)
{
    if (stack == NULL)
    {
        return 0;
    }

    return stack->top + 1;
}

ElementType as_top(const ArrayStack *stack)
{
    if (stack == NULL || stack->top == -1)
    {
        return 0;
    }

    return stack->nodes[stack->top].data;
}

int as_is_empty(const ArrayStack *stack)
{
    return stack == NULL || stack->top == -1;
}

int main(void)
{
    int i = 0;
    ArrayStack *stack = NULL;

    as_create_stack(&stack, 10);
    if (stack == NULL)
    {
        return 1;
    }

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
