#include <iostream>
#include "Grid.h"

template <typename T1, typename T2>
decltype(auto) add(const T1& t1, const T2& t2)
{
    return t1 + t2;
}

decltype(auto) add_abbreviated(const auto& t1, const auto& t2)
{
    return t1 + t2;
}

template <typename T>
constexpr T pi_templ{ T { static_cast<T>(3.14159) } };

void testGrid()
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

void testAddFunc()
{
    std::cout << add(2.1, 1);
    std::cout << std::endl << add_abbreviated(4.4, 2);
}

void testPItemplate()
{
    auto pi_float   { pi_templ<float> };
    auto pi_double  { pi_templ<double> };
    auto pi_int     { pi_templ<int> };
    
    std::cout << std::endl << pi_float << " " << pi_double << " " << pi_int;
}

int main()
{
    testAddFunc();
    testPItemplate();
}

