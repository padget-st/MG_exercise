//
//  main.cpp
//  strategy-pattern
//

#include <iostream>

class Person {
public:
    virtual void greet(const std::string & name) = 0;
};

class BusinessPerson : public Person {
public:
    void greet(const std::string & name) {
        std::cout << "Good morning " << name << ", how do you do?\n";
    }
};

class NormalPerson : public Person {
public:
    void greet(const std::string & name) {
        std::cout << "Hi " << name << ", how are you?\n";
    }
};

class CoolPerson : public Person {
public:
    void greet(const std::string & name) {
        std::cout << "Hey " << name << ", what's up?\n";
    }
};

// Uh oh - code duplication!
class Politician : public Person {
public:
    void greet(const std::string & name) {
        std::cout << "Good morning " << name << ", how do you do?\n";
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

