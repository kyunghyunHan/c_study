#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tag_node
{
    char *data;
    struct tag_node *next_node;
} node;

typedef struct tag_linked_list_stack
{
    node *list;
    node *top;

} linked_list_stack;

void lls_create_stack(linked_list_stack **stack);
void lls_destroy_stack(linked_list_stack *stack);
node *lls_create_node(const char *new_data);
void lls_destroy_node(node *target);
void lls_push(linked_list_stack *stack, node *new_node);
node *lls_pop(linked_list_stack *stack);
node *lls_top(linked_list_stack *stack);
int lls_get_size(linked_list_stack *stack);
int lls_is_empty(linked_list_stack *stack);

void lls_create_stack(linked_list_stack **stack)
{
    //  스택을 자유 저장소에 생성
    *stack = malloc(sizeof(linked_list_stack));
    (*stack)->list = NULL;
    (*stack)->top = NULL;
}

void lls_destroy_stack(linked_list_stack *stack)
{
    while (!lls_is_empty(stack))
    {
        node *popped = lls_pop(stack);
        lls_destroy_node(popped);
    }

    //  스택을 자유 저장소에서 해제
    free(stack);
}

node *lls_create_node(const char *new_data)
{
    node *new_node = malloc(sizeof(node));
    new_node->data = malloc(strlen(new_data) + 1);

    strcpy(new_node->data, new_data); //  데이터를 저장한다.

    new_node->next_node = NULL; //  다음 노드에 대한 포인터는 NULL로 초기화한다.

    return new_node; //  노드의 주소를 반환한다.
}

void lls_destroy_node(node *target)
{
    free(target->data);
    free(target);
}

void lls_push(linked_list_stack *stack, node *new_node)
{
    if (stack->list == NULL)
    {
        stack->list = new_node;
    }
    else
    {
        //  스택의 top에 신규 노드를 연결한다.
        stack->top->next_node = new_node;
    }

    //  스택의 top 필드에 새 노드의 주소를 등록한다.
    stack->top = new_node;
}

node *lls_pop(linked_list_stack *stack)
{
    //  lls_pop() 함수가 반환할 최상위 노드 저장
    node *top_node = stack->top;

    if (stack->list == stack->top)
    {
        stack->list = NULL;
        stack->top = NULL;
    }
    else
    {
        // top 아래에 있던 노드를 새로운 current_top에 저장
        node *current_top = stack->list;
        while (current_top != NULL && current_top->next_node != stack->top)
        {
            current_top = current_top->next_node;
        }

        // current_top을 top에 저장
        stack->top = current_top;
        stack->top->next_node = NULL;
    }

    return top_node;
}

node *lls_top(linked_list_stack *stack)
{
    return stack->top;
}

int lls_get_size(linked_list_stack *stack)
{
    int count = 0;
    node *current = stack->list;

    while (current != NULL)
    {
        current = current->next_node;
        count++;
    }

    return count;
}

int lls_is_empty(linked_list_stack *stack)
{
    return stack->list == NULL;
}

int main(void)
{
    int count = 0;
    node *popped = NULL;
    linked_list_stack *stack = NULL;

    lls_create_stack(&stack);

    lls_push(stack, lls_create_node("abc"));
    lls_push(stack, lls_create_node("def"));
    lls_push(stack, lls_create_node("efg"));
    lls_push(stack, lls_create_node("hij"));

    count = lls_get_size(stack);
    printf("size: %d, top: %s\n\n", count, lls_top(stack)->data);

    for (int i = 0; i < count; i++)
    {
        if (lls_is_empty(stack))
        {
            break;
        }

        popped = lls_pop(stack);

        printf("popped: %s, ", popped->data);

        lls_destroy_node(popped);

        if (!lls_is_empty(stack))
        {
            printf("current top: %s\n", lls_top(stack)->data);
        }
        else
        {
            printf("stack is empty.\n");
        }
    }

    lls_destroy_stack(stack);

    return 0;
}
