#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int mul(int a, int b)
{
    return a * b;
}

int divi(int a, int b)
{
    return a / b;
}

int mod(int a, int b)
{
    return a % b;
}

int end_op(int a, int b)
{
    (void)a;
    (void)b;
    printf("프로그램을 종료합니다.\n");
    return 0;
}

typedef struct
{
    const char *name;
    const char *sign;
    int (*func)(int, int);
} op_t;

void print_arr(const op_t *p, int menu_size)
{
    for (int i = 1; i < menu_size; ++i)
    {
        printf("%d. %s\n", i, p[i].name);
    }
    printf("0. %s\n", p[0].name);
}

int main(void)
{
    int a, b, id;
    const int menu_size = 6;
    const op_t menu[6] = {
        {"종료", "종료", end_op},
        {"덧셈", "+", add},
        {"뺄셈", "-", sub},
        {"곱셈", "*", mul},
        {"나눗셈(몫)", "/", divi},
        {"나눗셈(나머지)", "%", mod},
    };
    const op_t *op_ptr = NULL;

    while (1)
    {
        print_arr(menu, menu_size);
        printf("메뉴를 선택하세요: ");

        if (scanf("%d", &id) != 1)
        {
            printf("숫자를 입력해야 합니다.\n");
            return 1;
        }

        if (id < 0 || id >= menu_size)
        {
            printf("0부터 %d까지 입력하세요.\n\n", menu_size - 1);
            continue;
        }

        op_ptr = &menu[id];

        if (id == 0)
        {
            op_ptr->func(0, 0);
            break;
        }

        printf("두 정수를 입력하세요: ");
        if (scanf("%d %d", &a, &b) != 2)
        {
            printf("정수 두 개를 입력해야 합니다.\n");
            return 1;
        }

        if ((id == 4 || id == 5) && b == 0)
        {
            printf("0으로 나누거나 나머지를 구할 수 없습니다.\n\n");
            continue;
        }

        printf("결과는 %d %s %d = %d입니다.\n\n",
               a, op_ptr->sign, b, op_ptr->func(a, b));
    }

    return 0;
}
