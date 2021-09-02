//
//  main.cpp
//  interpreter-pattern
//

#include <iostream>

class Expression {
public:
    virtual int evaluate() = 0;
};

// 5 + (10 + 1)
class OperationExpression : public Expression {
    std::string operatorSymbol;
    Expression *leftHandSide;
    Expression *rightHandSide;
public:
    OperationExpression(const std::string & operatorSymbol, Expression *lhs, Expression *rhs) : operatorSymbol(operatorSymbol), leftHandSide(lhs), rightHandSide(rhs) {};
    int evaluate() override {
        if (operatorSymbol == "plus") {
            return leftHandSide->evaluate() + rightHandSide->evaluate();
        } else if (operatorSymbol == "minus") {
            return leftHandSide->evaluate() - rightHandSide->evaluate();
        } else {
            std::cout << "Unrecognized operator: " << operatorSymbol;
            return 0;
        }
    }
};

class NumberExpression : public Expression {
    std::string numberString;
public:
    NumberExpression(const std::string & numberString) : numberString(numberString) {};
    int evaluate() override {
        return std::stoi(numberString);
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
