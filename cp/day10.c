#include "day10_lib.h"

/*
배열 :
- 특징 : 같은 자료형의 데이터를 연속된 메모리 공간에 저장
- 장점 : 인덱스로 여러 데이터에 빠르게 접근 가능
- 사용처 : 점수 목록, 센서 데이터, 문자열, 버퍼, 행렬 등

포인터 :
- 특징 : 다른 변수나 데이터의 메모리 주소를 저장
- 장점 : 원본 데이터 직접 접근/수정, 동적 메모리, 배열/구조체 접근 가능
- 사용처 : 함수에서 원본 값 변경, 배열 전달, 구조체 전달,
          동적 메모리, 연결 리스트, 드라이버/임베디드 메모리 접근 등

함수 :
- 특징 : 특정 작업을 하나의 코드 단위로 분리
- 장점 : 모듈화, 유지보수, 재사용성, 가독성
- 사용처 : 반복되는 작업 분리, 프로그램 기능별 분리

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
int compint(const void *a, const void *b)
{
    const int value_a = *(const int *)a;
    const int value_b = *(const int *)b;

    return (value_a > value_b) - (value_a < value_b);
}
int comstr(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}

int compdouble(const void *a, const void *b)
{
    const double value_a = *(const double *)a;
    const double value_b = *(const double *)b;

    return (value_a > value_b) - (value_a < value_b);
}

void print_string03(const char *pary[], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        printf("%s%s", *(pary + i), i + 1 == count ? "\n" : " ");
    }
}

int comparr(const void *a, const void *b)
{
    const int *ra = a;
    const int *rb = b;

    for (int i = 0; i < 3; i++)
    {
        if (*(ra + i) > *(rb + i))
        {
            return 1;
        }
        if (*(ra + i) < *(rb + i))
        {
            return -1;
        }
    }
    return 0;
}
void qqsort(int (*arr)[3], int rows){
    for (int i = 0; i < rows; i++)
    {
        qsort(arr[i], 3, sizeof(int), compint);
    }

    qsort(arr, rows, sizeof(arr[0]), comparr);
};
int main(void)
{
    int a[10] = {5, 2, 8, 1, 9, 10, 4, 6, 7, 3};
    char *animal[5] = {"tiger", "cat", "lion", "dog", "elephant"};
    double b[5] = {2.3, 2.1, 2.6, 2.7, 2.4};
    int arr[5][3] = {
        {3, 5, 1},
        {1, 4, 3},
        {7, 1, 5},
        {3, 2, 2},
        {5, 3, 4},
    };

    qqsort(arr, 5);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d%s", arr[i][j], j == 2 ? "\n" : " ");
        }
    }

    return 0;
}
#endif

//  함수 포인터 활용
#if 00

typedef struct op_t
{
};

#define ARR_MAX (5)
int main(void)
{
    int a = 20, b = 5;
    int result[ARR_MAX] = {0};
    int res_1, res_2, res_3, res_4, res_5;
    int tot = 0;
    char *str[ARR_MAX] = {"sum", "sub", "mul", "divi", "mod"};
    int (*func[ARR_MAX])(int, int) = {add, sub, mul, divi, mod};
    tot = 0;
    res_1 = func[0](a, b);
    res_2 = sub(a, b);
    res_3 = mul(a, b);
    res_4 = divi(a, b);
    res_5 = mod(a, b);
    for (int i = 0; i < ARR_MAX; i++)
    {
        tot += (*(func + i))(a, b);
    }
    tot = res_1 + res_2 + res_3 + res_4 + res_5;
    printf("sum = %d\n", res_1);
    printf("sub = %d\n", res_2);
    printf("mul = %d\n", res_3);
    printf("divi = %d\n", res_4);
    printf("mod = %d\n", res_5);
    printf("tot = %d\n", tot);
    return 0;
}
#endif

#if 00
#endif

#if 1

/*
3차 사용자에게 어떤 연산을 할지에 대해 선택을 받고 동작 결과를 출력
1. 더하기
2. 뺴기
3. 곱하기
4.나누기

연산 번호를 입력 하시오 : 1
걀과는 20 + 5 = 25 입니다

*/
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
        printf("0. 결과 출력\n");
        printf("1. 더하기\n");
        printf("2. 빼기\n");
        printf("3. 곱하기\n");
        printf("4. 나누기\n");
        printf("연산 번호를 입력하세요: ");

        scanf("%d", &menu);

        switch (menu)
        {
        case 0:
            printf("종합: %d\n", total);
            break;

        case 1:
            printf("더하기 할 값 입력: ");
            scanf("%d", &input);

            total = ops[menu - 1].func(total, input);
            printf("현재 결과: %d\n", total);
            break;

        case 2:
            printf("빼기 할 값 입력: ");
            scanf("%d", &input);

            total = ops[menu - 1].func(total, input);
            printf("현재 결과: %d\n", total);
            break;

        case 3:
            printf("곱하기 할 값 입력: ");
            scanf("%d", &input);
            total = ops[menu - 1].func(total, input);
            printf("현재 결과: %d\n", total);
            break;

        case 4:
            printf("나누기 할 값 입력: ");
            scanf("%d", &input);

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
}
#endif
