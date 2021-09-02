//
//  main.cpp
//  visitor-pattern
//

#include <iostream>

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
