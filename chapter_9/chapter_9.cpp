import Spreadsheet_module;

#include <iostream>
#include <string>
#include <vector>

//void handleMessage(std::string& message)
//{
//    std::cout << message << " from &\n";
//}

void helper(std::string&& message)
{
    std::cout << message << " from helper&&\n";
}

void handleMessage(std::string&& message)
{
    std::cout << message << " from &&\n";
    helper(std::move(message));
}

void rvalueRefCheck1()
{
    std::string a{ "Hello " };
    handleMessage(std::move(a));

    std::string b{ " world!" };
    handleMessage(a + b);

    handleMessage("Rvalue");
}

void rvalueRefCheck2()
{
    int&& i{ 2 };
    int a{ 2 }, b{ 3 };
    int&& j{ a + b };

    std::cout << i << " " << j << std::endl;
}

//for testMoveOperators()
Spreadsheet createSpreadsheetObject(size_t x, size_t y)
{
    return Spreadsheet{ x, y };
}

void testMoveOperators()
{
    std::vector<Spreadsheet> vector;
    for (size_t i{}; i < 2; i++)
    {
        std::cout << "Iteration " << i << std::endl;
        vector.push_back(Spreadsheet{ i, i });
        std::cout << std::endl;
    }

    Spreadsheet s{ 2, 3 };
    s = createSpreadsheetObject(5, 6);

    Spreadsheet s2{ 6, 7 };
    s2 = s;
}

//testing ref-qualifiers
class TextHolder
{
private:
    std::string m_text;
public:
    TextHolder(std::string text) : m_text(std::move(text))
    {}

    const std::string& getText() const &
    {
        std::cout << "calls &\n";
        return m_text;
    }

    std::string&& getText() &&
    {
        std::cout << "calls &&\n";
        return std::move(m_text);
    }

    ~TextHolder()
    {
        std::cout << "before being destructed m_text has: "
            << m_text << std::endl;
    }
};

void testTextHolder()
{
    TextHolder th{ "Hello, World!" };
    std::cout << th.getText() << std::endl;
    std::cout << TextHolder{ "Hello, the second World!" }.getText() << std::endl;
    std::cout << std::move(th).getText() << std::endl;

    TextHolder th2{ TextHolder{"copy!"}.getText() };
}

int main()
{
    //testMoveOperators();
    testTextHolder();
}