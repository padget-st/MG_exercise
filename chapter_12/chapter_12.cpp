import NonTypeGrid_module;

#include <iostream>

template <typename T>
void printNonTypeGrid(const NonTypeGrid<T>& grid)
{
    for (size_t i{}; i < grid.getWidth(); i++)
    {
        for (size_t j{}; j < grid.getHeight(); j++)
        {
            std::cout << grid.at(i, j).value_or(-1) << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
void initNonTypeGrid(NonTypeGrid<T>& grid, T value = T{})
{
    for (size_t i{}; i < grid.getWidth(); i++)
    {
        for (size_t j{}; j < grid.getHeight(); j++)
        {
            grid.at(i, j) = value;
        }
    }
}

void testNonTypeGrid()
{
    NonTypeGrid grid;

    initNonTypeGrid(grid);

    {
        NonTypeGrid innerGrid;
        initNonTypeGrid(innerGrid, 3);
        NonTypeGrid secondInner{ std::move(innerGrid) };
        printNonTypeGrid(innerGrid);
        printNonTypeGrid(secondInner);
    }

    //printNonTypeGrid(grid);
}

int main()
{
    testNonTypeGrid();
}

