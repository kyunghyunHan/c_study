#pragma once

#include <list>

class SortPolicy
{
public:
    virtual ~SortPolicy() = default;
    virtual void sort(std::list<int>&) = 0;
};
