#include <stdio.h>
/*
연산 프로그램

1.메뉴출력
->0 종료 1.덧셈 2.뺄셈 3.곱셈 4.나눗셈 5.나머지
2.결과 표시 후 다시 1번 동작 반복
3.종료 ->프로그램 종료

*/

int add(int a, int b);

int sub(int a, int b);

int mul(int a, int b);

int divi(int a, int b);

int mod(int a, int b);

typedef struct
{
    const char *name;
    int (*func)(int, int);
} Op;

#define OP_COUNT 4

void init(Op ops[OP_COUNT]);

int main(void)
{
    Op ops[OP_COUNT];
    int menu;
    int total = 0;

    init(ops);

    while (1)
    {
        int input;

        printf("======================\n");
        printf("0. 종료\n");
        printf("1. 더하기\n");
        printf("2. 빼기\n");
        printf("3. 곱하기\n");
        printf("4. 나누기\n");
        printf("5. mod\n");
        printf("연산 번호를 입력하세요: ");

        scanf("%d", &menu);

        switch (menu)
        {
        case 0:
            printf("종료");
            return 0;

        case 1:
            printf("=====%s======\n", ops[menu - 1].name);
            printf("입력: ");
            scanf("%d", &input);
            printf("입력: %d", input);
            total = ops[menu - 1].func(total, input);
            printf("현재 결과: %d\n", total);
            break;

        case 2:
            printf("=====%s======\n", ops[menu - 1].name);
            printf("입력: ");
            scanf("%d", &input);
            printf("입력: %d", input);
            total = ops[menu - 1].func(total, input);
            printf("현재 결과: %d\n", total);
            break;

        case 3:
            printf("=====%s======\n", ops[menu - 1].name);
            printf("입력: ");
            scanf("%d", &input);
            printf("입력: %d", input);
            total = ops[menu - 1].func(total, input);
            printf("현재 결과: %d\n", total);
            break;

        case 4:
            printf("=====%s======\n", ops[menu - 1].name);
            printf("입력: ");
            scanf("%d", &input);
            printf("입력: %d", input);
            total = ops[menu - 1].func(total, input);
            printf("현재 결과: %d\n", total);
            break;
        case 5:
            printf("=====%s======\n", ops[menu - 1].name);
            printf("입력: ");
            scanf("%d", &input);
            printf("입력: %d", input);
            total = ops[menu - 1].func(total, input);
            printf("현재 결과: %d\n", total);
            break;
        default:
            printf("0부터 4까지의 번호를 입력하세요.\n");
            break;
        }
    }
    return 0;
}

void init(Op ops[OP_COUNT])
{
    ops[0] = (Op){"더하기", add};
    ops[1] = (Op){"빼기", sub};
    ops[2] = (Op){"곱하기", mul};
    ops[3] = (Op){"나누기", divi};
    ops[4] = (Op){"나눈값", mod};
}

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