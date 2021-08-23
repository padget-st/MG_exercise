module;

#include <string>
#include <string_view>
#include <memory>

export module PersonInter_module;

export class PersonInter
{
private:
    class PersonImpl;
    std::unique_ptr<PersonImpl> m_PersonImpl;

public:
    PersonInter();
    PersonInter(const std::string& firstName, const std::string& lastName);
    PersonInter(std::string firstName, std::string lastName, std::string initials);
    PersonInter(const PersonInter& PersonInter);
    PersonInter(PersonInter&& PersonInter) noexcept;

    PersonInter& operator=(const PersonInter& rhPerson);
    PersonInter& operator=(PersonInter&& rhPerson) noexcept;

    ~PersonInter();

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

//export void printPersonInter(const PersonInter& PersonInter);