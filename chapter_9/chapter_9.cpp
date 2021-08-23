import Spreadsheet_module;
//import Person_module;
import PersonInter_module;

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


//UNRESOLVED ERROR: dereferencing nullptr
void printPersonInter(const PersonInter& PersonInter)
{
    std::cout << "\nFirst name: " << PersonInter.getFirstName() << std::endl
        << "Last name: " << PersonInter.getLastName() << std::endl
        << "Initials: " << PersonInter.getInitials() << std::endl << std::endl;
}

//test function for exercise9_1
void exercise9_1()
{
    //normal ctor and delegating
    PersonInter pers1("John", "Doe");
    printPersonInter(pers1);

    //normal ctor
    PersonInter pers2("Frank", "Joe", "F.J.");
    printPersonInter(pers2);

    //copy ctor
    PersonInter pers3{ pers1 };
    printPersonInter(pers3);

    //copy assignment and copy ctor
    pers3 = pers2;
    printPersonInter(pers3);

    //move ctor
    PersonInter pers4{ std::move(pers1) };
    printPersonInter(pers4);
    printPersonInter(pers1);

    //move ctor and move assignment
    pers2 = PersonInter{ std::move(pers4) };
    printPersonInter(pers2);
    printPersonInter(pers4);
}

//test function for exercise9_2 and 9_3
void exercise9_2and3()
{
    PersonInter pers1{ "John", "Doe" }, pers2{ "Mark", "Allis" };
    std::cout << (pers1 == pers2) << std::endl;
    std::cout << (pers1 != pers2) << std::endl;
    std::cout << (pers1 <= pers2) << std::endl;
    std::cout << (pers1 >= pers2) << std::endl;
    std::cout << (pers1 < pers2) << std::endl;
    std::cout << (pers1 > pers2) << std::endl;
    //0 1 1 0 1 0
}

int main()
{
    //testMoveOperators();
    //testTextHolder();
    //exercise9_2and3();

    PersonInter pint("john", "doe", "J.D.");
    exercise9_2and3();
    exercise9_1();
}