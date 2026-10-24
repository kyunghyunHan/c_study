#include "SortFactory.h"
#include "BubbleSort.h"
#include "QuickSort.h"
#include <stdexcept>

SortPolicy *SortFactory::getSortPolicy(int type)
{
    switch (type)
    {
    case 1:
        return new QuickSort;
    case 2:
        return new BubbleSort;
    }

    throw std::invalid_argument("Unknown sort type");
}
