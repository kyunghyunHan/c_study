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

#if 1
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
