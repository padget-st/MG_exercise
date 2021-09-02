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
    void accept(Visitor *v) { v->handlePerson(name, age); };
};

class Landmark {
    std::string name;
    std::string cityName;
public:
    Landmark(const std::string & name, const std::string & cityName) : name(name), cityName(cityName) {};
    void accept(Visitor *v) { v->handleLandmark(name, cityName); };
};

class Car {
    std::string make;
    std::string model;
public:
    Car(const std::string & make, const std::string & model) : make(make), model(model) {};
    void accept(Visitor *v) { v->handleCar(make, model); };
};

int main(int argc, const char * argv[]) {
    Person person("John", 40);
    Landmark landmark("Eiffel Tower", "Paris");
    Car car("Chevrolet", "Camaro");
    
    DatabaseVisitor *dbv = new DatabaseVisitor;
    TextFileVisitor *tfv = new TextFileVisitor;
    
    person.accept(dbv);
    landmark.accept(dbv);
    car.accept(dbv);
    
    person.accept(tfv);
    landmark.accept(tfv);
    car.accept(tfv);
    
    delete dbv;
    delete tfv;
    
    return 0;
}
