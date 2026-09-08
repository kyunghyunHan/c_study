#include "calculator.h"

#include <stdio.h>
#include <string.h>

char number[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};

int is_number(char cipher)
{
    int i = 0;
    int array_length = sizeof(number);

    for (i = 0; i < array_length; i++)
    {
        if (cipher == number[i])
        {
            return 1;
        }
    }
    return 0;
}
unsigned int get_next_token(char *expression, char *token, int *type)
{
    unsigned int i = 0;
    unsigned int token_position = 0;

    while (expression[i] != '\0')
    {
        if (is_number(expression[i]) == 1)
        {
            *type = OPERAND;
            if (token_position < 31)
            {
                token[token_position++] = expression[i];
            }
            i++;

            if (is_number(expression[i]) != 1)
            {
                break;
            }
        }
        else
        {
            token[token_position++] = expression[i];
            *type = expression[i];
            i++;
            break;
        }
    }
    token[token_position] = '\0';
    return i;
}
int get_priority(char operator, int in_stack)
{
    int priority = -1;

    switch (operator)
    {
    case LEFT_PARENTHESIS:
        if (in_stack)
        {
            priority = 3;
        }
        else
        {
            priority = 0;
        }
        break;

    case MULTIPLY:
    case DIVIDE:
        priority = 1;
        break;
    case PLUS:
    case MINUS:
        priority = 2;
        break;
    }

    return priority;
}
int is_prior(char operator_in_stack, char operator_in_token)
{
    return (get_priority(operator_in_stack, 1) > get_priority(operator_in_token, 0));
}

void get_postfix(char *in_fix_expression, char *postfix_expression)
{
    LinkedListStack *stack;
    char token[32];
    int type = -1;
    unsigned int postion = 0;
    unsigned int length = strlen(in_fix_expression);

    lls_create_stack(&stack);

    while (postion < length)
    {
        postion += get_next_token(&in_fix_expression[postion], token, &type);

        if (type == OPERAND)
        {
            strcat(postfix_expression, token);
            strcat(postfix_expression, " ");
        }
        else if (type == RIGHT_PARENTHESIS)
        {
            while (!lls_is_empty(stack))
            {
                Node *popped = lls_pop(stack);

                if ((*popped).data[0] == LEFT_PARENTHESIS)
                {
                    lls_destroy_node(popped);
                    break;
                }
                else
                {
                    strcat(postfix_expression, (*popped).data);
                    lls_destroy_node(popped);
                }
            }
        }
        else
        {
            while (!lls_is_empty(stack) && !is_prior(lls_top(stack)->data[0], token[0]))
            {
                Node *popped = lls_pop(stack);
                if ((*popped).data[0] != LEFT_PARENTHESIS)
                {
                    strcat(postfix_expression, (*popped).data);
                }
                lls_destroy_node(popped);
            }
            lls_push(stack, lls_create_node(token));
        }
    }
    while (!lls_is_empty(stack))
    {
        Node *popped = lls_pop(stack);
        if (popped->data[0] != LEFT_PARENTHESIS)
        {
            strcat(postfix_expression, popped->data);
        }
        lls_destroy_node(popped);
    }
    lls_destroy_stack(stack);
}

double calculate(char *post_fix_expression)
{
    LinkedListStack *stack;
    Node *result_node;

    double result;
    char token[32];
    int type = -1;
    unsigned int read = 0;
    unsigned int length = strlen(post_fix_expression);

    lls_create_stack(&stack);

    while (read < length)
    {
        read += get_next_token(&post_fix_expression[read], token, &type);

        if (type == SPACE)
        {
            continue;
        }
        if (type == OPERAND)
        {
            Node *new_node = lls_create_node(token);
            lls_push(stack, new_node);
        }
        else
        {
            char result_string[32];
            double operator1, operator2, temp_result = 0.0;
            Node *operator_node;

            if (lls_get_size(stack) < 2)
            {
                lls_destroy_stack(stack);
                return 0.0;
            }

            operator_node = lls_pop(stack);
            operator2 = atof(operator_node->data);
            lls_destroy_node(operator_node);

            operator_node = lls_pop(stack);
            operator1 = atof(operator_node->data);
            lls_destroy_node(operator_node);

            switch (type)
            {
            case PLUS:
                temp_result = operator1 + operator2;
                break;
            case MINUS:
                temp_result = operator1 - operator2;
                break;
            case MULTIPLY:
                temp_result = operator1 * operator2;
                break;
            case DIVIDE:
                temp_result = operator1 / operator2;
                break;
            default:
                lls_destroy_stack(stack);
                return 0.0;
            }
            snprintf(result_string, sizeof(result_string), "%.10g", temp_result);
            lls_push(stack, lls_create_node(result_string));
        }
    }

    result_node = lls_pop(stack);
    if (result_node == NULL)
    {
        lls_destroy_stack(stack);
        return 0.0;
    }
    result = atof(result_node->data);
    lls_destroy_node(result_node);
    lls_destroy_stack(stack);
    return result;
}

int main(void)
{
    char in_fix_expression[100];
    char post_fix_expression[200];

    double result = 0.0;
    memset(in_fix_expression, 0, sizeof(in_fix_expression));
    memset(post_fix_expression, 0, sizeof(post_fix_expression));

    printf("Enter Infix Expression:");
    if (scanf("%99s", in_fix_expression) != 1)
    {
        return 1;
    }

    get_postfix(in_fix_expression, post_fix_expression);
    printf("infix:%s\nPostfix:%s\n", in_fix_expression, post_fix_expression);

    result = calculate(post_fix_expression);
    printf("Calculation Result : %f\n", result);
    return 0;
}
