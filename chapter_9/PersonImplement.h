#pragma once

#include <string>
#include <string_view>
#include <iostream>
#include <memory>

class PersonInter
{
private:
    class PersonImpl;
    std::unique_ptr<PersonImpl> m_PersonImpl;

public:
    PersonInter() = default;
    PersonInter(const std::string& firstName, const std::string& lastName);
    PersonInter(std::string firstName, std::string lastName, std::string initials);
    PersonInter(const PersonInter& PersonInter);
   // PersonInter(PersonInter&&) noexcept;

    PersonInter& operator=(const PersonInter& rhPerson);
    //PersonInter& operator=(PersonInter&& rhPerson) noexcept;
    //pre-C++20 implementation
    bool operator==(const PersonInter& rhPerson) const;
    bool operator!=(const PersonInter& rhPerson) const;
    bool operator>(const PersonInter& rhPerson) const;
    bool operator<(const PersonInter& rhPerson) const;
    bool operator>=(const PersonInter& rhPerson) const;
    bool operator<=(const PersonInter& rhPerson) const;

    inline const std::string& getFirstName() const;
    inline void setFirstName(std::string newFirstName);

    inline const std::string& getLastName() const;
    inline void setLastName(std::string newLastName);

    inline const std::string& getInitials() const;
    inline void setInitials(std::string newInitials);
};