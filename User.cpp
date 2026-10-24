#include "User.h"
#include "SortFactory.h"
#include <iostream>

User::User(std::list<int> &numbers) : numbers(numbers)
{
}

void User::sort_number()
{
    SortFactory *factory = new SortFactory;
    SortPolicy *sortPolicy = factory->getSortPolicy(1);
    std::list<int> numbers = {1, 2, 2,1,3,4};


    sortPolicy->sort(numbers);


    for (int number : numbers)
        std::cout << number << ' ';

        
    delete sortPolicy;
    delete factory;
}
