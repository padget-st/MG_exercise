#include <iostream>
#include "Grid.h"

int main()
{
    
    Grid<> grid_int;
    grid_int.at(2, 2) = 8;
    grid_int.setData(13);
    std::cout << grid_int.at(2, 2).value_or(0.0) << " " << grid_int.getData() << '\n';

    Grid<double, 11, 11> grid_double;
    grid_double.setData(4.3);
    grid_double.at(2, 2) = 4;
    std::cout << grid_double.at(2, 2).value_or(0.0) << " " << grid_double.getData() << '\n';

    grid_double = grid_int;
    std::cout << grid_double.at(2, 2).value_or(0.0) << " " << grid_double.getData();
}

