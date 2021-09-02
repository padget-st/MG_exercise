//
//  main.cpp
//  template-method-pattern
//

#include <iostream>

class GreetingCardTemplate {
protected:
    virtual std::string intro(const std::string & to) {
        return "Dear " + to + ",\n";
    }
    virtual std::string occasion() {
        return "Just writing to say hi! Hope all is well with you.\n";
    }
    virtual std::string closing(const std::string & from) {
        return "Sincerely,\n" + from + "\n";
    }
public:
    std::string generate(const std::string & to, const std::string & from) {
        return intro(to) + occasion() + closing(from);
    }
};

class BirthdayCardTemplate : public GreetingCardTemplate {
protected:
    std::string occasion() override {
        return "Happy birthday!! Hope you have a wonderful day and lots of cake.\n";
    }
};

class NewYearsCardTemplate : public GreetingCardTemplate {
protected:
    std::string intro(const std::string & to) override {
        return to + "!!!\n";
    }
    std::string occasion() override {
        return "Happy New Years!!!! See you at the gym tomorrow!\n";
    }
};

int main(int argc, const char * argv[]) {
    GreetingCardTemplate gct;
    BirthdayCardTemplate bct;
    NewYearsCardTemplate nyct;
    
    std::cout << "Here's a regular greeting card:\n\n" << gct.generate("Bob", "Jane") << "\n";
    std::cout << "Here's a birthday card:\n\n" << bct.generate("Bob", "Jane") << "\n";
    std::cout << "Here's a new year's card:\n\n" << nyct.generate("Bob", "Jane") << "\n";
    
    return 0;
}
