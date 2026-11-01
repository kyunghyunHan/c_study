#pragma once

#include "SortPolicy.h"

class QuickSort : public SortPolicy
{
public:
    void sort(std::list<int> &numbers) override;
};
