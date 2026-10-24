#pragma once
#include <list>
class User
{
public:
    explicit User(std::list<int> &numbers);
    void sort_number();

private:
    std::list<int> &numbers;
};
