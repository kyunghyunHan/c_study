#pragma once
#include "SortPolicy.h"
class BubbleSort : public SortPolicy
{
public:
    void sort(std::list<int> &numbers) override;
};
