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

class NumberCollection {
    std::vector<int> numbers;
public:
    NumberCollection(const std::vector<int> & numbers) : numbers(numbers) {};
    NumberIterator *getForwardsIterator() { return new ForwardsIterator(numbers); };
    NumberIterator *getBackwardsIterator() { return new BackwardsIterator(numbers); };
};

int main(int argc, const char * argv[]) {
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7 };
    NumberCollection nc(numbers);
    
    NumberIterator *fi = nc.getForwardsIterator();
    NumberIterator *bi = nc.getBackwardsIterator();
    
   while (!fi->isFinished()) {
       std::cout << fi->next() << ", ";
   }
   
   std::cout << "\n";
   
   std::cout << "Iterating through the numbers backwards:\n";
   
   while (!bi->isFinished()) {
       std::cout << bi->next() << ", ";
   }
   
   std::cout << "\n";

    delete fi;
    delete bi;
    
    return 0;
}
