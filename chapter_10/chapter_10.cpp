#include <iostream>

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

int main()
{
    
}
