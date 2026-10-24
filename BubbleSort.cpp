#include "BubbleSort.h"
#include <iterator>
#include <utility>

void BubbleSort::sort(std::list<int> &numbers)
{
    if (numbers.size() < 2)
        return;

    for (auto end = numbers.end(); end != numbers.begin(); --end)
    {
        bool swapped = false;
        auto previous = numbers.begin();
        for (auto current = std::next(previous); current != end; ++current)
        {
            if (*previous > *current)
            {
                std::swap(*previous, *current);
                swapped = true;
            }
            previous = current;
        }
        if (!swapped)
            break;
    }
}
