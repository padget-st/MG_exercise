export module Person_module;

#include <string>
#include <iostream>
#include <string_view>

export class Person
{
private:
    std::string m_firstName{ "N/A" };
    std::string m_lastName{ "N/A" };
    std::string m_initials{ "?.?." };

    std::string generateInitials(std::string_view firstName,
        std::string_view lastName);
public:
    Person() = default;
    Person(const std::string& firstName, const std::string& lastName);
    Person(std::string firstName, std::string lastName, std::string initials);
    Person(const Person& person);
    Person(Person&& person);

    Person& operator=(const Person& rhPerson);
    Person& operator=(Person&& rhPerson);

    ~Person();

    inline const std::string& getFirstName() const { return m_firstName; }
    inline void setFirstName(std::string newFirstName) { m_firstName = std::move(newFirstName); }

    inline const std::string& getLastName() const { return m_lastName; }
    inline void setLastName(std::string newLastName) { m_lastName = std::move(newLastName); }

    inline const std::string& getInitials() const { return m_initials; };
    inline void setInitials(std::string newInitials) { m_initials = std::move(newInitials); }
};

std::string Person::generateInitials(std::string_view firstName,
    std::string_view lastName)
{
    std::string tempInitials{};
    tempInitials = tempInitials + firstName.front() + ".";
    tempInitials = tempInitials + lastName.front() + ".";
    return tempInitials;//(N)RVO
}

Person::Person(std::string firstName, std::string lastName, std::string initials)
    : m_firstName{ std::move(firstName) }, m_lastName{ std::move(lastName) },
    m_initials{ std::move(initials) }
{
    std::cout << "Normal ctor\n";
}

Person::Person(const std::string& firstName, const std::string& lastName)
    : Person{ firstName, lastName, generateInitials(firstName, lastName) }
{
    std::cout << "Delegating ctor\n";
}

Person::Person(const Person& person) : m_firstName{ person.getFirstName() },
    m_lastName{ person.getLastName() }, m_initials{ person.getInitials() }
{
    std::cout << "Copy ctor\n";
}

Person& Person::operator=(const Person& rhPerson)
{
    std::cout << "Copy assignment\n";
    if (this == &rhPerson) { return *this; }
    m_firstName = rhPerson.getFirstName();
    m_lastName = rhPerson.getLastName();
    return *this;
}

Person::~Person()
{
    std::cout << "Destructor\n";
}

export void printPerson(const Person& person)
{
    std::cout << "First name: " << person.getFirstName() << std::endl
        << "Last name: " << person.getLastName() << std::endl
        << "Initials: " << person.getInitials() << std::endl;
}
