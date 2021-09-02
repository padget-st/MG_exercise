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
    SomeTask() {
        logger = new NullLogger;
    }
    SomeTask(Logger *logger) : logger(logger) {};
    ~SomeTask() { delete logger; };
    void execute() {
        // Do some stuff...
        
        logger->log("Did some stuff");
        
        // Do some other stuff...

        logger->log("Did some other stuff");
        
        // One last thing...
        
        logger->log("Task complete!");
    }
};

int main(int argc, const char * argv[]) {
    SomeTask task1(new ConsoleLogger);
    SomeTask task2(new FileLogger("logs.txt"));
    SomeTask task3(new ApiLogger("loggingsite.com/api/logs"));
    SomeTask task4;
    
    task1.execute();
    task2.execute();
    task3.execute();
    task4.execute();
    
    return 0;
}
