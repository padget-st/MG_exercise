//
//  main.cpp
//  null-object-pattern
//

#include <iostream>
#include <stdio.h>

class Logger {
public:
    virtual ~Logger() {};
    virtual void log(const std::string & message) = 0;
};

class ConsoleLogger : public Logger {
public:
    void log(const std::string & message) override {
        std::cout << message << "\n";
    }
};

class FileLogger :  public Logger {
    std::string filePath;
public:
    FileLogger(const std::string & filePath) : filePath(filePath) {};
    void log(const std::string & message) override {
        std::cout << "Printing message to file " << filePath << ": " << message << "\n";
    }
};

class ApiLogger : public Logger {
    std::string url;
public:
    ApiLogger(const std::string & url) : url(url) {};
    void log(const std::string & message) override {
        std::cout << "Sending message to api " << url << ": " << message << "\n";
    }
};

class NullLogger : public Logger {
public:
    void log(const std::string & message) override {};
};

class SomeTask {
    Logger *logger = nullptr;
public:
    SomeTask(Logger *logger) : logger(logger) {};
    ~SomeTask() { delete logger; };
    void execute() {
        // Do some stuff...
        
        if (logger) {
            logger->log("Did some stuff");
        }
        
        // Do some other stuff...
        
        if (logger) {
            logger->log("Did some other stuff");
        }
        
        // One last thing...
        
        if (logger) {
            logger->log("Task complete!");
        }
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
