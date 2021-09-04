import NonTypeGrid_module;
import KeyValuePair_nodule;

#include <iostream>
#include <numbers>

template <typename T, size_t WIDTH, size_t HEIGHT>
void printNonTypeGrid(const NonTypeGrid<T, WIDTH, HEIGHT>& grid)
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

template <typename T, size_t WIDTH, size_t HEIGHT>
void initNonTypeGrid(NonTypeGrid<T, WIDTH, HEIGHT>& grid, T value = T{})
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
    NonTypeGrid<double, 5, 5> grid;

    initNonTypeGrid(grid);

    {
        NonTypeGrid innerGrid;
        initNonTypeGrid(innerGrid, 3);
        NonTypeGrid secondInner{ std::move(innerGrid) };
        printNonTypeGrid(innerGrid);
        printNonTypeGrid(secondInner);
        grid = secondInner;
    }

    printNonTypeGrid(grid);
}

template<typename T>
std::optional<size_t> findOptional(const T& value, const T* arr, size_t size)
{
    for (size_t i{}; i < size; i++)
    {
        if (arr[i] == value)
        {
            return i;
        }
    }
    return {};
}

template <typename T, size_t N>
decltype(auto) findOptional(const T& value, const T(&arr)[N])
{
    return findOptional(value, arr, N);
}

void testFindOptional()
{
    int value{ 2 };
    int intArr[]{ 1, 2, 3, 4, 5 };

    const size_t size1{ std::size(intArr) };
    const size_t size2{ sizeof(intArr) / sizeof(int) };
    
    if (size1 == size2)
    {
        //auto res{ findOptional(value, intArr, size1) };
        auto res{ findOptional(value, intArr) };
        if (res.has_value())
        {
            std::cout << "Found value's index: " << res.value() << std::endl;
        }
        else
        {
            std::cout << "Not found\n";
        }
    }
    else
    {
        std::cout << "Sizes didn't match\n";
    }
}

template <typename T>
constexpr T pi{ T{3.14159} };

void testVarTemplate()
{
    float floatPI{ pi<float> };
    auto doublePI{ pi<double> };
    std::cout << floatPI << " " << doublePI << std::endl;
}



void exercise12_1()
{
    KeyValuePair<int, double> intDoublePair{ 12, 3.5 };
    printKeyValuePair(intDoublePair);

    intDoublePair.setKey(10);
    intDoublePair.setValue(4.7);
    printKeyValuePair(intDoublePair);

    //CTAD
    KeyValuePair somePair(1.1, 2.3);
}

void exercise12_2()
{
    KeyValuePair strPair("John Doe", "New York");
    printKeyValuePair(strPair);
}

int main()
{
    exercise12_2();
}

