module;

#include <string>
#include <iostream>
#include <string_view>

export module Person_module;

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
    Person(const Person& Person);
    Person(Person&& Person) noexcept;

    void swap(Person& rhPerson) noexcept;

    Person& operator=(const Person& rhPerson);
    Person& operator=(Person&& rhPerson) noexcept;

    ~Person();

    //first implementation of exercise9_2
    //[[nodiscard]] bool operator==(const PersonInter& rhPerson) const;
    //[[nodiscard]] auto operator<=>(const PersonInter& rhPerson) const;

    //second implementation of exercise9_2
    //[[nodiscard]] auto operator<=>(const PersonInter& rhPerson) const = default;

    //pre-C++20 implementation
    bool operator==(const Person& rhPerson) const;
    bool operator!=(const Person& rhPerson) const;
    bool operator>(const Person& rhPerson) const;
    bool operator<(const Person& rhPerson) const;
    bool operator>=(const Person& rhPerson) const;
    bool operator<=(const Person& rhPerson) const;

    inline const std::string& getFirstName() const;
    inline void setFirstName(std::string newFirstName);

    inline const std::string& getLastName() const;
    inline void setLastName(std::string newLastName);

    inline const std::string& getInitials() const;
    inline void setInitials(std::string newInitials);
};

void Person::swap(Person& rhPerson) noexcept
{
    std::swap(m_firstName, rhPerson.m_firstName);
    std::swap(m_lastName, rhPerson.m_lastName);
    std::swap(m_initials, rhPerson.m_initials);
}

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
    //std::cout << "Normal ctor\n";
}

Person::Person(const std::string& firstName, const std::string& lastName)
    : Person{ firstName, lastName, generateInitials(firstName, lastName) }
{
    //std::cout << "Delegating ctor\n";
}

Person::Person(const Person& Person) : m_firstName{ Person.getFirstName() },
    m_lastName{ Person.getLastName() }, m_initials{ Person.getInitials() }
{
    //std::cout << "Copy ctor\n";
}

Person::Person(Person&& rhPerson) noexcept
{
    //std::cout << "Move ctor\n";
    swap(rhPerson);
}

Person& Person::operator=(const Person& rhPerson)
{
    //std::cout << "Copy assignment\n";
    auto temp{ rhPerson };
    swap(temp);
    return *this;
}

Person& Person::operator=(Person&& rhPerson) noexcept
{
    //std::cout << "Move assignment\n";
    swap(rhPerson);
    return *this;
}

Person::~Person()
{
    //std::cout << "Destructor\n";
}

//first impl. of exercise9_2
//bool PersonInter::operator==(const PersonInter& rhPerson) const
//{
//    return (getLastName() == rhPerson.getLastName());
//}
//
//auto PersonInter::operator<=>(const PersonInter& rhPerson) const
//{
//    return (getLastName() <=> rhPerson.getLastName());
//}

//pre-C++20 implementation for exercise9_3
bool Person::operator==(const Person& rhPerson) const
{
    return (getFirstName() == rhPerson.getFirstName()
        && getLastName() == rhPerson.getLastName()
        && getInitials() == rhPerson.getInitials());
}

bool Person::operator!=(const Person& rhPerson) const
{
    return !(*this == rhPerson);
}

bool Person::operator>(const Person& rhPerson) const
{
    return (getFirstName() > rhPerson.getFirstName()) ||
         (getFirstName() == rhPerson.getFirstName() &&
             getLastName() > rhPerson.getLastName()) ||
        (getFirstName() == getFirstName() &&
            getLastName() == getLastName() &&
        getInitials() > rhPerson.getInitials());
}

bool Person::operator<(const Person& rhPerson) const
{
    return !(*this > rhPerson);
}

bool Person::operator>=(const Person& rhPerson) const
{
    return (*this > rhPerson || *this == rhPerson);
}

bool Person::operator<=(const Person& rhPerson) const
{
    return (*this < rhPerson || *this == rhPerson);
}

inline const std::string& Person::getFirstName() const { return m_firstName; }

inline void Person::setFirstName(std::string newFirstName) { m_firstName = std::move(newFirstName); }

inline const std::string& Person::getLastName() const { return m_lastName; }

inline void Person::setLastName(std::string newLastName) { m_lastName = std::move(newLastName); }

inline const std::string& Person::getInitials() const { return m_initials; };

inline void Person::setInitials(std::string newInitials) { m_initials = std::move(newInitials); }

//export void printPerson(const Person& PersonInter)
//{
//    std::cout << "\nFirst name: " << PersonInter.getFirstName() << std::endl
//        << "Last name: " << PersonInter.getLastName() << std::endl
//        << "Initials: " << PersonInter.getInitials() << std::endl << std::endl;
//}
