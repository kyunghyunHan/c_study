typedef int ElementType;

typedef struct tagNode
{
    ElementType Data;
} Node;

typedef struct tagAarrayStack
{
    int capacity;
    int top;
    Node *nodes;
} ArrayStack;

void as_create_stack(ArrayStack **stack, int capacity)
{
    // 스택을 자유 저장소에 생성
    (*stack) = (ArrayStack *)malloc(sizeof(ArrayStack));

    // 입력된 capacity만큼 노드를 자유저장소에 생성
    (*stack)->nodes = (Node *)malloc(sizeof(Node) * capacity);

    // capacity 및 top 초기화
    (*stack)->capacity = capacity;
    (*stack)->top = -1;
}

void as_detroy_stack(ArrayStack *stack)
{
    // node를 자유 저장소에서 해제
    free((*stack).nodes);

    // 스택을 자유 저장소에서 해제
    free(stack);
}

void as_push(ArrayStack *stack, ElementType data)
{
    stack->top++;
    stack->nodes[stack->top].data = data;
}