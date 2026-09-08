#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdlib.h>
#include "list_stack.h"

typedef enum
{
    LEFT_PARENTHESIS = '(',
    RIGHT_PARENTHESIS = ')',
    PLUS = '+',
    MINUS = '-',
    MULTIPLY = '*',
    DIVIDE = '/',
    SPACE = ' ',
    OPERAND
} SYMBOL;

int is_number(char cipher);
unsigned int get_next_token(char *expression, char *token, int *type);
int get_priority(char operator, int in_stack);
int is_prior(char operator1, char operator2);
void get_postfix(char *in_fix_expression, char *postfix_expression);
double calculate(char *post_fix_expression);

#endif
