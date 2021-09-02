//
//  main.cpp
//  strategy-pattern
//

#include <iostream>

class GreetingStrategy {
public:
    virtual ~GreetingStrategy() {};
    virtual void greet(const std::string & name) = 0;
};

class FormalGreetingStrategy : public GreetingStrategy {
public:
    void greet(const std::string & name) {
        std::cout << "Good morning " << name << ", how do you do?\n";
    }
};

class NormalGreetingStrategy : public GreetingStrategy {
public:
    void greet(const std::string & name) {
        std::cout << "Hi " << name << ", how are you?\n";
    }
};

class InformalGreetingStrategy : public GreetingStrategy {
public:
    void greet(const std::string & name) {
        std::cout << "Hey " << name << ", what's up?\n";
    }
};

// NOTE - this code won't compile since there's no Person class now.
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
