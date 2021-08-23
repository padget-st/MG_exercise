import PersonInter_module;

#include <string>
#include <string_view>
#include <iostream>

class PersonInter::PersonImpl
{
private:
    std::string m_firstName{ "N/A" };
    std::string m_lastName{ "N/A" };
    std::string m_initials{ "?.?." };

    std::string generateInitials(std::string_view firstName,
        std::string_view lastName);
public:
    PersonImpl() = default;
    PersonImpl(std::string firstName, std::string lastName);
    PersonImpl(std::string firstName, std::string lastName, std::string initials);

    inline const std::string& getFirstName() const;
    inline void setFirstName(std::string newFirstName);

    inline const std::string& getLastName() const;
    inline void setLastName(std::string newLastName);

    inline const std::string& getInitials() const;
    inline void setInitials(std::string newInitials);
};

PersonInter::PersonImpl::PersonImpl(std::string firstName, std::string lastName)
    : m_firstName{ std::move(firstName) }, m_lastName{ std::move(lastName) }
{
    m_initials = generateInitials(m_firstName, m_lastName);
}

PersonInter::PersonImpl::PersonImpl(std::string firstName, std::string lastName,
    std::string initials) : m_firstName{ std::move(firstName) }, m_lastName{ std::move(lastName) },
    m_initials{ std::move(initials) }
{

}

PersonInter::~PersonInter() = default;
PersonInter::PersonInter(PersonInter&& rhPerson) noexcept = default;
PersonInter& PersonInter::operator=(PersonInter&&) noexcept = default;

inline const std::string& PersonInter::PersonImpl::getFirstName() const { return m_firstName; }

inline void PersonInter::PersonImpl::setFirstName(std::string newFirstName) { m_firstName = std::move(newFirstName); }

inline const std::string& PersonInter::PersonImpl::getLastName() const { return m_lastName; }

inline void PersonInter::PersonImpl::setLastName(std::string newLastName) { m_lastName = std::move(newLastName); }

inline const std::string& PersonInter::PersonImpl::getInitials() const { return m_initials; };

inline void PersonInter::PersonImpl::setInitials(std::string newInitials) { m_initials = std::move(newInitials); }

std::string PersonInter::PersonImpl::PersonImpl::generateInitials(std::string_view firstName,
    std::string_view lastName)
{
    std::string tempInitials{};
    tempInitials = tempInitials + firstName.front() + ".";
    tempInitials = tempInitials + lastName.front() + ".";
    return tempInitials;//(N)RVO
}

PersonInter::PersonInter()
    : m_PersonImpl{ std::make_unique<PersonImpl>() }
{

}

PersonInter::PersonInter(std::string firstName, std::string lastName, std::string initials)
    : m_PersonImpl{ std::make_unique<PersonImpl>(std::move(firstName), std::move(lastName),
    std::move(initials)) }
{
    std::cout << "Normal ctor\n";
}

PersonInter::PersonInter(const std::string& firstName, const std::string& lastName)
    : m_PersonImpl{ std::make_unique<PersonImpl>(std::move(firstName), std::move(lastName)) }
{
    std::cout << "Delegating ctor\n";
}

PersonInter::PersonInter(const PersonInter& PersonInter)
    : m_PersonImpl{ std::make_unique<PersonImpl>(*PersonInter.m_PersonImpl) }
{
    std::cout << "Copy ctor\n";
}

PersonInter& PersonInter::operator=(const PersonInter & rhPerson)
{
    std::cout << "Copy assignment\n";
    *m_PersonImpl = *rhPerson.m_PersonImpl;
    return *this;
}

//pre-C++20 implementation for exercise9_3
bool PersonInter::operator==(const PersonInter & rhPerson) const
{
    return (getFirstName() == rhPerson.getFirstName()
        && getLastName() == rhPerson.getLastName()
        && getInitials() == rhPerson.getInitials());
}

bool PersonInter::operator!=(const PersonInter & rhPerson) const
{
    return !(*this == rhPerson);
}

bool PersonInter::operator>(const PersonInter & rhPerson) const
{
    return (getFirstName() > rhPerson.getFirstName()) ||
        (getFirstName() == rhPerson.getFirstName() &&
            getLastName() > rhPerson.getLastName()) ||
        (getFirstName() == getFirstName() &&
            getLastName() == getLastName() &&
            getInitials() > rhPerson.getInitials());
}

bool PersonInter::operator<(const PersonInter & rhPerson) const
{
    return !(*this > rhPerson);
}

bool PersonInter::operator>=(const PersonInter & rhPerson) const
{
    return (*this > rhPerson || *this == rhPerson);
}

bool PersonInter::operator<=(const PersonInter & rhPerson) const
{
    return (*this < rhPerson || *this == rhPerson);
}

inline const std::string& PersonInter::getFirstName() const { return m_PersonImpl->getFirstName(); }

inline void PersonInter::setFirstName(std::string newFirstName) { m_PersonImpl->setFirstName(std::move(newFirstName)); }

inline const std::string& PersonInter::getLastName() const { return m_PersonImpl->getLastName(); }

inline void PersonInter::setLastName(std::string newLastName) { m_PersonImpl->setLastName(std::move(newLastName)); }

inline const std::string& PersonInter::getInitials() const { return m_PersonImpl->getInitials(); };

inline void PersonInter::setInitials(std::string newInitials) { m_PersonImpl->setInitials(std::move(newInitials)); }

//void printPersonInter(const PersonInter& PersonInter)
//{
//    std::cout << "\nFirst name: " << PersonInter.getFirstName() << std::endl
//        << "Last name: " << PersonInter.getLastName() << std::endl
//        << "Initials: " << PersonInter.getInitials() << std::endl << std::endl;
//}