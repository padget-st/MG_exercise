#include <iostream>
#include <string>
#include <charconv>

int main()
{
    const int buffer_size{ 20 };
    double value1{ 0.123 };
    std::string out(buffer_size, ' ');
    auto str_to_chars{std::to_chars(out.data(), out.data() + out.size(), value1)};
    if (str_to_chars.ec == std::errc{})
    {
        std::cout << out << " " << out.size() << std::endl;
    }

    double value2{};
    auto chars_to_str{std::from_chars(out.data(), out.data() + out.size(), value2)};
    if (chars_to_str.ec == std::errc{})
    {
        std::cout << value2;
        if (value1 == value2) { std::cout << " - perfect roundtrip\n"; }
        else { std::cout << " - Smth went wrong\n"; }
    }
}