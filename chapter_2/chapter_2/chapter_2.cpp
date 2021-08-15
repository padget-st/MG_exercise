#include <iostream>
#include <string>
#include <charconv>
#include <vector>
#include <format>

std::string getStringFromUser()
{
    std::string temp_str;
    std::getline(std::cin, temp_str);
    return temp_str;
}

void askAndPrintTwoStrings()
{
    std::string s1, s2;

    std::cout << "Enter the first line: ";
    s1 = getStringFromUser();
    std::cout << "Enter the second line: ";
    s2 = getStringFromUser();
    
    auto compare_result{ s1 <=> s2 };
    if (std::is_lt(compare_result) || std::is_eq(compare_result))
    {
        std::cout << s1 << std::endl << s2;
    }
    else
    {
        std::cout << s2 << std::endl << s1;
    }
}

std::string replaceAllNeedles(std::string_view haystack,
    std::string_view needle, std::string_view replacement)
{
    std::string result{ haystack.data() };
    while (true)
    {
        auto position{ result.find(needle.data()) };
        if (position == std::string::npos)
        {
            break;
        }

        result.replace(position, needle.size(), replacement.data());
    }
    return result;
}

void findAndReplace()
{
    std::string haystack, needle, replace;
    std::cout << "Enter a haystack: ";
    haystack = getStringFromUser();
    std::cout << "Enter a needle: ";
    needle = getStringFromUser();
    std::cout << "Enter a replace: ";
    replace = getStringFromUser();

    std::cout << replaceAllNeedles(haystack, needle, replace);
}

void askAndFormatFloatNums()
{
    std::vector<float> v_fl;
    float user_input{};

    while (std::cin >> user_input && user_input != 0)
    {
        v_fl.push_back(user_input);
    }

    for (auto& elem : v_fl)
    {
        std::cout << std::format("|{0:<+#10e}|{0:*^#10.3F}|{0:010.1F}|\n", elem);
    }
}

int main()
{
    //const int buffer_size{ 20 };
    //double value1{ 0.123 };
    //std::string out(buffer_size, ' ');
    //auto str_to_chars{std::to_chars(out.data(), out.data() + out.size(), value1)};
    //if (str_to_chars.ec == std::errc{})
    //{
    //    std::cout << out << " " << out.size() << std::endl;
    //}

    //double value2{};
    //auto chars_to_str{std::from_chars(out.data(), out.data() + out.size(), value2)};
    //if (chars_to_str.ec == std::errc{})
    //{
    //    std::cout << value2;
    //    if (value1 == value2) { std::cout << " - perfect roundtrip\n"; }
    //    else { std::cout << " - Smth went wrong\n"; }
    //}
    
    askAndFormatFloatNums();
}