//
//  main.cpp
//  chain-of-responsibility
//
//

#include <iostream>
#include <vector>
#include <regex>

class StringValidator {
public:
    virtual StringValidator *setNext(StringValidator *nextValidator) = 0;
    virtual ~StringValidator() {};
    virtual std::string validate(std::string) = 0;
};

class BaseValidator : public StringValidator {
protected:
    StringValidator *next = nullptr;
public:
    ~BaseValidator() { delete next; };
    StringValidator *setNext(StringValidator *nextValidator) override {
        next = nextValidator;
        return nextValidator;
    }
    virtual std::string validate(std::string testString) override {
        if (this->next) {
            return this->next->validate(testString);
        }
        return "Success!";
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
