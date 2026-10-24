#include <iostream>
#include "User.h"

int main()
{
    std::list<int> numbers = {5, 3, 8, 1, 2, 7, 4, 6};
    User user(numbers);
    user.sort_number();
    for (int number : numbers)
        std::cout << number << ' ';
    std::cout << '\n';
}
