#ifndef list_stack_h
#define list_stack_h

typedef struct tagNode
{
    char *data;
    struct tagNode *next_node;
} Node;

typedef struct tagLinkedListStack
{
    Node *list;
    Node *top;
} LinkedListStack;

void lls_create_stack(LinkedListStack **stack);
void lls_destroy_stack(LinkedListStack *stack);

Node *lls_create_node(const char *new_data);
void lls_destroy_node(Node *target);

void lls_push(LinkedListStack *stack, Node *new_node);
Node *lls_pop(LinkedListStack *stack);
Node *lls_top(LinkedListStack *stack);

int lls_get_size(LinkedListStack *stack);
int lls_is_empty(LinkedListStack *stack);

#endif
