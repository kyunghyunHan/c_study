#include "calculator.h";

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
    for (int i = 0; 0 != expression[i]; i++)
    {
        token[i] = expression[i];

        if (is_number(expression[i]) == 1)
        {
            *type = OPERAND;

            if (is_number(expression[i + 1]) != 1)
            {
                break;
            }
        }
    }
}
int main(void)
{
    return 0;
}