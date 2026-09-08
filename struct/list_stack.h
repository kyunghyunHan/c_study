#ifndef list_stack_h
#define list_stack_h

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

#endif
