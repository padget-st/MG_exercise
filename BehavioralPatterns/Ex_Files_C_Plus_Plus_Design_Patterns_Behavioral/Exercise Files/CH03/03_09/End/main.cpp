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

class Person {
    GreetingStrategy *greetingStrategy;
public:
    Person(GreetingStrategy *greetingStrategy) : greetingStrategy(greetingStrategy) {};
    ~Person() { delete greetingStrategy; };
    void greet(const std::string & name) {
        greetingStrategy->greet(name);
    }
};

int main(int argc, const char * argv[]) {
    Person businessPerson(new FormalGreetingStrategy());
    Person normalPerson(new NormalGreetingStrategy());
    Person coolPerson(new InformalGreetingStrategy());
    Person politician(new FormalGreetingStrategy());
    
    std::cout << "The businessperson says: ";
    businessPerson.greet("Shaun");
    
    std::cout << "The normal person says: ";
    normalPerson.greet("Shaun");
    
    std::cout << "The cool person says: ";
    coolPerson.greet("Shaun");
    
    std::cout << "The politician says: ";
    politician.greet("Shaun");
    
    return 0;
}
