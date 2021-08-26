#include <iostream>
#include <vector>
#include "StringSpreadsheetCell.h"
#include "DoubleSpreadsheetCell.h"
#include "Director.h"
#include "Manager.h"

class Base
{
private:
    int m_privateMember{};
    int m_privateProtectedMember{};
protected:
    int getPrivateProtected() const { return m_privateProtectedMember; }
public:
    Base(int value) : m_privateMember{ value } {}
    int getPrivate() const { return m_privateMember; }
    virtual void someMethod() const { std::cout << "Base: someMethod\n"; }
    virtual ~Base() = default;
};

class Derived : public Base
{
public:
    Derived(int value) : Base{ value } {}
    void someMethod() const override
    {std::cout << "Derived: someMethod\n";}
    virtual ~Derived() = default;
};

void testDowncasting(Base* base)
{
    Base* baseTemp{ base };
    baseTemp->someMethod();

    Derived* derivTemp{ dynamic_cast<Derived*>(base) };
    if (derivTemp)
    {
        derivTemp->someMethod();
    }
}

void testPolymorph()
{
    std::vector<std::unique_ptr<SpreadsheetCell>> vectorCell;
    
    vectorCell.push_back(std::make_unique<DoubleSpreadsheetCell>());
    vectorCell.push_back(std::make_unique<StringSpreadsheetCell>());

    vectorCell[0]->set("10");
    vectorCell[1]->set("20");

    std::cout << (vectorCell[0]->getString() + vectorCell[1]->getString());
}

class Cherry
{
public:
    static void beStatic()
    {
        std::cout << "Cherry: static\n";
    }

    virtual void printName() const
    {
        std::cout << "Cherry!\n";
    }

    virtual ~Cherry() = default;
};

class BingCherry : public Cherry
{
public:
    static void beStatic()
    {
        Cherry::beStatic();
        std::cout << "BingCherry: static\n";
    }

    void printName() const override
    {
        std::cout << "BingCherry!\n";
    }
    virtual void polish()
    {
        std::cout << "BingCherry: polished\n";
    }

    virtual ~BingCherry() = default;
};

class Loggable
{
public:
    virtual ~Loggable() = default;
    virtual std::string getLogMessage() const = 0;
};

class CherryTree : public Loggable
{
private:
    virtual void privateFunc() const
    {
        std::cout << "CherryTree: privateFunc\n";
    }
public:
    virtual void grow()
    {
        std::cout << "Cherry tree has grown up!\n";
    }

    virtual Cherry* pick()
    {
        return new Cherry{};
    }

    std::string getLogMessage() const override
    {
        return "log from CherryTree\n";
    }

    virtual ~CherryTree() = default;
};

class BingCherryTree : public CherryTree
{
    void privateFunc() const override
    {
        std::cout << "BingCherryTree: privateFunc\n";
    }
public:
    using CherryTree::grow;

    void callPrivateFunc() const
    {
        privateFunc();
    }

    virtual void grow(int meters)
    {
        std::cout << "BingCherryTree has grown up " << meters << " meters tall\n";
    }

    BingCherry* pick() override
    {
        auto tempCherry{ std::make_unique<BingCherry>() };
        tempCherry->polish();
        return tempCherry.release();
    }

    std::string getLogMessage() const override
    {
        return "log from BingCherryTree\n";
    }

    virtual ~BingCherryTree() = default;
};

void logObject(const Loggable& logObj)
{
    std::cout << typeid(logObj).name() << ": "
        << logObj.getLogMessage() << std::endl;
}

void testCherry()
{
    BingCherryTree bct;
    CherryTree ct;

    logObject(bct);
    logObject(ct);

    bct.callPrivateFunc();

    ct.grow();
    bct.grow();
    bct.grow(3);

    //std::unique_ptr<Cherry> theCherry1{ bct.pick() };
    Cherry* theCherry1{ bct.pick() };
    std::unique_ptr<Cherry> theCherry2{ ct.pick() };
    theCherry1->printName();
    theCherry2->printName();
    
    auto theCherry3 = reinterpret_cast<BingCherry*>(theCherry1);
    theCherry3->polish();
    theCherry3->printName();

    theCherry3->beStatic();
}

void testBitCast()
{
    float asFloat{ 1.23f };
    auto asUint{ std::bit_cast<unsigned int>(asFloat) };
    if (std::bit_cast<float>(asUint) == asFloat)
    {
        std::cout << "Roundtrip!";
    }
}

void printPersonRef(const HR::Person& person)
{
    std::cout << person.getFirstName() << " "
        << person.getLastName() << " "
        << person.getInitials() << " "
        << person.toString() << std::endl;
}

void testPersonHierarchy()
{
    HR::Person person{ "John", "Doe" };
    printPersonRef(person);

    HR::Employee employee{ "Steeve", "Bam", 43 };
    printPersonRef(employee);

    HR::Manager manager{ "Rob", "Bob", 45 };
    printPersonRef(manager);

    HR::Director director{ "Vin", "Vega", 1 };
    printPersonRef(director);
    
}

void testPolymorphPerson()
{
    std::vector<std::unique_ptr<HR::Person>> v;

    v.push_back(std::make_unique<HR::Director>("Charlie", "Brown", 45));
    v.push_back(std::make_unique<HR::Person>("Carl", "Johnson"));
    v.push_back(std::make_unique<HR::Manager>("Hloie", "Matt", 25));
    v.push_back(std::make_unique<HR::Director>("Markus", "Turn", 145));
    v.push_back(std::make_unique<HR::Employee>("Sid", "Crown", 51));

    for (const auto& elem : v)
    {
        std::cout << elem->toString() << std::endl;
    }
}

void testPromoting()
{
    HR::Employee empl("Mark", "Gorge", 45);
    printPersonRef(empl);

    HR::Manager manager(std::move(empl));
    printPersonRef(manager);
}

int main()
{

}
