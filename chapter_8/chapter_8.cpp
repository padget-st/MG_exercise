#include <iostream>
#include <string>
#include <string_view>

import SpreadsheetCell_module;

//Exercise 8_1
class Person
{
private:
    std::string m_firstName{"N/A"};
    std::string m_lastName{"N/A"};
    std::string m_initials{ "?.?." };
    
    std::string generateInitials(const std::string& firstName,
        const std::string lastName)
    {
        std::string tempInitials{};
        tempInitials = tempInitials + firstName.front() + ".";
        tempInitials = tempInitials + lastName.front() + ".";
        return tempInitials;
    }
public:
    //the default ctor for the "exercise8_2" function
    Person() = default;

    Person(const std::string& firstName, const std::string& lastName)
        : Person{firstName, lastName, generateInitials(firstName, lastName)}
    {}

    //for exercise8_4()
    Person(const std::string& firstName, const std::string& lastName,
        const std::string& initials)
        : m_firstName{firstName}, m_lastName{lastName}, m_initials{initials}
    {}

    //the copy constructor for the "exercise8_3" function
    //Person(const Person& person) : m_firstName{ person.getFirstName() },
    //    m_lastName{person.getLastName()}
    //{
    //    std::cout << "\nCopy ctor\n";
    //}
    // 
    //the copy assignment for the "exercise8_3" function
    //Person& operator=(const Person& rhPerson)
    //{
    //    std::cout << "\nCopy assignment\n";
    //    if (this == &rhPerson) { return *this; }
    //    m_firstName = rhPerson.getFirstName();
    //    m_lastName = rhPerson.getLastName();
    //    return *this;
    //}
    // 
    //the copy destructor for the "exercise8_3" function
    ~Person()
    {
        std::cout << "\nDestructor\n";
    }

    const std::string& getFirstName() const { return m_firstName; }
    void setFirstName(const std::string& newFirstName) { m_firstName = newFirstName; }

    const std::string& getLastName() const { return m_lastName; }
    void setLastName(const std::string& newLastName) { m_lastName = newLastName; }

    const std::string& getInitials() const { return m_initials; };
    void setInitials(const std::string& newInitials) { m_initials = newInitials; }
};

void printPerson(const Person& person)
{
    std::cout << "First name: " << person.getFirstName() << std::endl
        << "Last name: " << person.getLastName() << std::endl;
}

void exercise8_1()
{
    //stack
    Person stackPerson("John", "Doe");
    printPerson(stackPerson);
    stackPerson.setFirstName("Ben");
    stackPerson.setLastName("Allen");
    printPerson(stackPerson);

    //free
    auto freePersonPtr{ std::make_unique<Person>("Joe", "Lann")};
    printPerson(*freePersonPtr);
    freePersonPtr->setFirstName("Mike");
    freePersonPtr->setLastName("Milton");
    printPerson(*freePersonPtr);
}

void exercise8_2()
{
    Person phoneBook[3];
    printPerson(phoneBook[1]);
}

void exercise8_3()
{
    Person person1("John", "Doe");
    //copy
    Person person2{ person1 };
    //copy
    Person person3 = person2;
    Person person4;
    //assignment
    person4 = person3;
}

void exercise8_4()
{
    Person person("Xan", "Tent");
    printPerson(person);
    std::cout << "Initials: " << person.getInitials() << std::endl;
}

int main()
{
    SpreadsheetCell cell;
    cell.setString("test1a");
    std::cout << cell.getValue() << std::endl;

    //exercise8_1();
    //exercise8_2();
    //exercise8_3();
    exercise8_4();
}
