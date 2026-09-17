#include <stdlib.h>
#include <stdio.h>
#include "point.h"
/*
데이터의 중앙에 있는 요소 고름
중앙 요소값과 찾고자 하는 목표값을 비교
목표값이 중앙 요소값보다 작다면 중앙을 기준으로 데이터 왼편에 대해
크다면 오른편에 대해 이진 탐색 수행
찾고자 하는 값을 찾을때마다 1~3 수행

*/
Point *BinarySearch(Point PointList[], int Size, double Target)
{
    int Left, Right, Mid;

    Left = 0;
    Right = Size - 1;

    while (Left <= Right) // 탐색 범위의 크기가 0이 될떄까지 while문 반복
    {
        Mid = (Left + Right) / 2; // 중앙의 요소 위치를 계산

        if (Target == PointList[Mid].point)
            return &(PointList[Mid]);
        else if (Target > PointList[Mid].point)
            Left = Mid + 1; // 오른쪽에 타겟이 있으니 left계산
        else
            Right = Mid - 1; // 왼쪽에 값이 있으니 right을 계산
    }

    return NULL;
}

int ComparePoint(const void *_elem1, const void *_elem2)
{
    Point *elem1 = (Point *)_elem1;
    Point *elem2 = (Point *)_elem2;

    if (elem1->point > elem2->point)
        return 1;
    else if (elem1->point < elem2->point)
        return -1;
    else
        return 0;
}

int main(void)
{
#if 0 int Length = sizeof DataSet / sizeof DataSet[0];
    Point *found = NULL;

    //  구매포인트에 대해 오름차순으로 정렬
    qsort((void *)DataSet, Length, sizeof(Point), ComparePoint);

    //  671.78 포인트 고객 찾기
    found = BinarySearch(DataSet, Length, 671.78);

    printf("found... ID: %d, Point: %f \n", found->id, found->point);

    return 0;
#endif

    int length = sizeof DataSet / sizeof DataSet[0];
    Point target;
    Point *found = NULL;

    qsort((void *)DataSet, length, sizeof(Point), ComparePoint);

    // 구매 포인트가  671.78
    target.id = 0;
    target.point = 671.78;

    found = bsearch((void *)&target, (void *)DataSet, length, sizeof(Point), ComparePoint);

    printf("found... ID: %d, Point: %f \n", found->id, found->point);

    return 0;
}