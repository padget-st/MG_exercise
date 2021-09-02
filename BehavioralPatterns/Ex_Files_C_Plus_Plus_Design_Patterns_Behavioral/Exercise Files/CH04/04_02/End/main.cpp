//
//  main.cpp
//  iterator-pattern
//

#include <iostream>
#include <vector>

class NumberIterator {
public:
    virtual ~NumberIterator() {};
    virtual int next() = 0;
    virtual bool isFinished() = 0;
};

class ForwardsIterator: public NumberIterator {
    int currentPosition;
    std::vector<int> &numbers;
public:
    ForwardsIterator(std::vector<int> &numbers) : currentPosition(0), numbers(numbers) {};
    int next() override {
        int current = numbers.at(currentPosition);
        currentPosition += 1;
        return current;
    }
    bool isFinished() override {
        return currentPosition >= numbers.size();
    }
};

class BackwardsIterator: public NumberIterator {
    int currentPosition;
    std::vector<int> &numbers;
public:
    BackwardsIterator(std::vector<int> &numbers) : currentPosition(0), numbers(numbers) {};
    int next() override {
        int current = numbers.at(numbers.size() - currentPosition - 1);
        currentPosition += 1;
        return current;
    }
    bool isFinished() override {
        return currentPosition >= numbers.size();
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
