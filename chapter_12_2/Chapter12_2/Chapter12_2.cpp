#include <iostream>
#include <string>
#include <concepts>
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

template <std::integral K, std::floating_point V> 
class KeyValuePair
{
public:
    KeyValuePair(const K& key, const V& value);

    void setKey(const K& key);
    K getKey() const;

    void setValue(const V& value);
    V getValue() const;

private:
    K m_key;
    V m_value;
};

template<std::integral K, std::floating_point V>
KeyValuePair<K, V>::KeyValuePair(const K& key, const V& value)
    : m_key{ key }, m_value{ value } {}

template<std::integral K, std::floating_point V>
void KeyValuePair<K, V>::setKey(const K& key) { m_key = key; };

template<std::integral K, std::floating_point V>
K KeyValuePair<K, V>::getKey() const { return m_key; };

template<std::integral K, std::floating_point V>
void KeyValuePair<K, V>::setValue(const V& value) { m_value = value; };

template<std::integral K, std::floating_point V>
V KeyValuePair<K, V>::getValue() const { return m_value; };

/*template <>
class KeyValuePair< const char*, const char* >
{
public:
    KeyValuePair(const char* key, const char* value)
        : m_key{ key }, m_value{ value } {}

    void setKey(const char* key) { m_key = key; }
    std::string getKey() const { return m_key; }

    void setValue(const char* value) { m_value = value; }
    std::string getValue() const { return m_value; }

private:
    std::string m_key{};
    std::string m_value{};
};*/

template <typename T>
concept ConvertsToString = requires(const T & x) { std::to_string(x); };

auto concat(const ConvertsToString auto& t1, const ConvertsToString auto& t2)
{
    return std::to_string(t1) + std::to_string(t2);
}

auto concat(std::string_view t1, std::string_view t2)
{
    return std::string{ t1 } + std::string{ t2 };
}

auto concat(std::string_view t1, const ConvertsToString auto& t2)
{
    return std::string{ t1 } + std::to_string( t2 );
}

auto concat(const ConvertsToString auto& t1, std::string_view t2)
{
    return std::to_string( t1 ) + std::string{ t2 };
}

void testKeyValuePair() //exercise 1
{
    /*KeyValuePair<double, Grid<>> pair(1.1, Grid());

    pair.setKey(2.2);
    Grid<> grid;
    grid.at(1, 1) = 17;
    pair.setValue(grid);
    std::cout << std::endl << pair.getKey() << " " << pair.getValue().at(1, 1).value_or(0);*/
}

void testKeyValuePairString() //exercise 2
{
    /*KeyValuePair<const char*, const char*> str_pair("Marion", "Krane");
    std::cout << std::endl << str_pair.getKey() << " " << str_pair.getValue();*/
}

void testKeyValuePairIntFloat() //exercise 3
{
    KeyValuePair<int, double> pair(4, 4.4);
    std::cout << std::endl << pair.getKey() << " " << pair.getValue();
}

void testConcatFirst() //exercise 4
{
    std::cout << concat(2.5, 4);
}

void testConcatSecond() //exercise 5
{
    std::cout << concat(4, 2.5)
        << '\n' << concat("str", 2.5)
        << '\n' << concat(2.5, "str")
        << '\n' << concat("str", "str");
}

int main()
{
    testConcatSecond();
}

