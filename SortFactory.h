#pragma once

#include "SortPolicy.h"

class SortFactory
{
public:
    SortFactory() = default;

    // 1: 퀵소트, 2: 버블 정렬
    // 반환된 객체는 호출한 쪽에서 delete로 해제합니다.
    SortPolicy *getSortPolicy(int type);
};
