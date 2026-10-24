#include "QuickSort.h"
#include <iterator>

void QuickSort::sort(std::list<int> &numbers)
{
    if (numbers.size() < 2)
        return;

    const int pivot = *std::next(numbers.begin(), numbers.size() / 2);
    std::list<int> lower;
    std::list<int> equal;
    std::list<int> higher;

    while (!numbers.empty())
    {
        auto current = numbers.begin();
        if (*current < pivot)
            lower.splice(lower.end(), numbers, current);
        else if (*current > pivot)
            higher.splice(higher.end(), numbers, current);
        else
            equal.splice(equal.end(), numbers, current);
    }

    sort(lower);
    sort(higher);

    numbers.splice(numbers.end(), lower);
    numbers.splice(numbers.end(), equal);
    numbers.splice(numbers.end(), higher);
}
