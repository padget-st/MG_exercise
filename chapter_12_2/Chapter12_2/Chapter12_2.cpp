#include <iostream>
#include "Grid.h"

int main()
{
    
    Grid<int> grid_int;
    grid_int.at(2, 2) = 8;
    std::cout << grid_int.at(2, 2).value_or(0);
}

