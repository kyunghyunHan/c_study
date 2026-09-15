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
*(&*(*(*a+2) +1))  = >  4

*a+2 =
*/
#endif

#if 0
// void *memmove(void *dest, const void *src, size_t size);
//  memmove();

void compint()P_ALL
void swap02(void *ap, void *bp, int size)
{
    void *temp = NULL;
    temp = malloc(size);
    memmove(temp, ap, size);
    memmove(ap, bp, size);
    memmove(bp, temp, size);
    free(temp);
}
void sort(int *ary, int n)
{
    int s = n - 1;
    for (int i = 0; i < s; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (ary[i] > ary[j])
            {
                int temp;

                memmove(&temp, &ary[i], sizeof(temp));
                memmove(&ary[i], &ary[j], sizeof(ary[i]));
                memmove(&ary[j], &temp, sizeof(ary[j]));
            }
        }
    }
}

int main(void)
{
    int ary[5] = {4, 2, 5, 1, 3};

    sort(ary, 5);

    for (int i = 0; i < 5; i++)
    {
        printf("%d%s", ary[i], i == 4 ? "\n" : " ");
    }

    return 0;
}
#endif

#if 0

void swap_02(void *ap, void *bp, int size)
{
    void *temp = NULL;
    temp = malloc(size);
    memmove(temp, ap, size);
    memmove(ap, bp, size);
    memmove(bp, temp, size);
    free(temp);
}

int compint01(const void *a, const void *b)
{
    int ia = *(int *)a;
    int ib = *(int *)b;
    if (ia == ib)
        return 0;
    if (ia > ib)
        return 1;
    return -1;
}

int compint(const void *a, const void *b)
{
    int ia = *(int *)a;
    int ib = *(int *)b;
    return (ia > ib) - (ia < ib); //  3가지 연산 (<, >, -)가 무조건 수행되는 단점이 있음
}
int compstr(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}

int compdouble(const void *a, const void *b)
{
    double da = *(double *)a;
    double db = *(double *)b;
    if (da > db)
        return 1;
    if (da < db)
        return -1;
    return 0;
}

// 정렬 - 함수포인터활용
void sort(void *base, int num, int size, int (*comp)(void *, void *))
{
    char *cbase = (char *)base;
    void *a;
    void *b;
    int s = num - 1;
    for (int i = 0; i < s; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            a = cbase + i * size;
            b = cbase + j * size;
            if (comp(a, b) > 0)
            {
                swap_02(a, b, size);
            }
        }
    }
}
#endif
#if 0
void swap_03(void *a, void *b, int size)
{
    char *temp = NULL;
    temp = malloc(size);
    if (temp == NULL)
    {
        return;
    }
    memmove(temp, a, size);
    memmove(a, b, size);
    memmove(b, temp, size);
    free(temp);
}
void sort_int(int *ary, int num)
{
    int s = num - 1;
    for (int i = 0; i < s; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            if (ary[i] > ary[j])
            {
                // int temp = *(ary + i);
                // *(ary + i) = *(ary + j);
                // *(ary + j) = temp;
                swap_03(ary + i, ary + j, sizeof(*ary));
            }
        }
    }
}
int main(void)
{
    int ary[5] = {4, 2, 5, 1, 3};
    sort_int(ary, 5);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", ary[i]);
    }
    return 0;
}
#endif

void swap_03(void *a, void *b, int size)
{
    char *temp = NULL;
    temp = malloc(size);
    if (temp == NULL)
    {
        return;
    }
    memmove(temp, a, size);
    memmove(a, b, size);
    memmove(b, temp, size);
    free(temp);
}
void sort_int(int *ary, int num)
{
    int s = num - 1;
    for (int i = 0; i < s; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            if (ary[i] > ary[j])
            {
                // int temp = *(ary + i);
                // *(ary + i) = *(ary + j);
                // *(ary + j) = temp;
                swap_03(ary + i, ary + j, sizeof(*ary));
            }
        }
    }
}
// base : 배열의 시작주소
// num : 배열의 요소 개수
// size : 1개 요소의 크기

int compint_02(const void *a, const void *b)
{
    int ia = *(int *)a;
    int ib = *(int *)b;
    if (ia > ib)
        return 1;
    if (ia < ib)
        return -1;
    return 0;
}
void my_sort(void *base, int num, int size,
             int (*comp)(const void *, const void *))
{
    char *cbase = (char *)base;
    int s = num - 1;
    for (int i = 0; i < s; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            char *a = cbase + (i * size);
            char *b = cbase + (j * size);
            if (comp(a, b) > 0)
            {
                // int temp = *(ary + i);
                // *(ary + i) = *(ary + j);
                // *(ary + j) = temp;
                swap_03(a, b, size);
            }
        }
    }
}
int main(void)
{
    int ary[5] = {4, 2, 5, 1, 3};
    my_sort(ary, SIZE(ary), sizeof(*ary), compint_02);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", ary[i]);
    }
    return 0;
}
