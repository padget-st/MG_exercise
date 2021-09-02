//
//  main.cpp
//  state-pattern
//

#include <iostream>

class Purchase {
    std::string productName;
    std::string currentState;
public:
    Purchase(const std::string & productName)
        : productName(productName), currentState("PURCHASED") {};
    std::string getDescription() {
        std::string description = productName + " - " + currentState + "\n";
        
        if (currentState == "PURCHASED") {
            description += "Will be shipping soon\n";
        } else if (currentState == "IN_TRANSIT") {
            description += "Your item is on the way\n";
        } else if (currentState == "DELIVERED") {
            description += "Your item has arrived\n";
        }
        
        return description;
    }
    
    void goToNextState() {
        if (currentState == "PURCHASED") {
            currentState = "IN_TRANSIT";
        } else if (currentState == "IN_TRANSIT") {
            currentState = "DELIVERED";
        } else if (currentState == "DELIVERED") {
            std::cout << "No more states!";
        }
    };
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
