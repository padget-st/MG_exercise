//
//  main.cpp
//  visitor-pattern
//

#include <iostream>

class Visitor {
public:
    virtual void handlePerson(const std::string & name, int age) = 0;
    virtual void handleLandmark(const std::string & name, const std::string & cityName) = 0;
    virtual void handleCar(const std::string & make, const std::string & model) = 0;
};

class DatabaseVisitor : public Visitor {
public:
    void handlePerson(const std::string & name, int age) override {
        std::cout << "Writing person to database: " << name << ", " << age << "\n";
    };
    void handleLandmark(const std::string & name, const std::string & cityName) override {
        std::cout << "Writing landmark to database: " << name << ", " << cityName << "\n";
    };
    void handleCar(const std::string & make, const std::string & model) override {
        std::cout << "Writing car to database: " << make << ", " << model << "\n";
    };
};

class TextFileVisitor : public Visitor {
public:
    void handlePerson(const std::string & name, int age) override {
        std::cout << "Writing person to file: " << name << ", " << age << "\n";
    };
    void handleLandmark(const std::string & name, const std::string & cityName) override {
        std::cout << "Writing landmark to file: " << name << ", " << cityName << "\n";
    };
    void handleCar(const std::string & make, const std::string & model) override {
        std::cout << "Writing car to file: " << make << ", " << model << "\n";
    };
};

class Person {
    std::string name;
    int age;
public:
    Person(const std::string & name, int age) : name(name), age(age) {};
};

class Landmark {
    std::string name;
    std::string cityName;
public:
    Landmark(const std::string & name, const std::string & cityName) : name(name), cityName(cityName) {};
};

class Car {
    std::string make;
    std::string model;
public:
    Car(const std::string & make, const std::string & model) : make(make), model(model) {};
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
