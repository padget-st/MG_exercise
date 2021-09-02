//
//  main.cpp
//  mediator-pattern
//
//

#include <iostream>

class InterfaceElement {
protected:
    std::string name;
    bool isVisible = true;
public:
    InterfaceElement(const std::string & name, bool isVisible) : name(name), isVisible(isVisible) {};
    void setVisibility(bool isVisible) { this->isVisible = isVisible; };
    std::string getDescription() {
        return isVisible
            ? name + " is visible"
            : name + " is NOT visible";
    }
};

class ButtonElement : public InterfaceElement {
public:
    ButtonElement(const std::string & name, bool isVisible) : InterfaceElement(name, isVisible) {};
    virtual ~ButtonElement() {};
    virtual void click() = 0;
};

class TextBox : public InterfaceElement {
    std::string textValue = "";
public:
    TextBox(const std::string & name, bool isVisible) : InterfaceElement(name, isVisible) {};
    virtual ~TextBox() {};
    virtual void changeText(const std::string & newValue) { textValue = newValue; };
};

class CheckBox : public InterfaceElement {
    bool isChecked = false;
public:
    CheckBox(const std::string & name, bool isVisible) : InterfaceElement(name, isVisible) {};
    virtual ~CheckBox() {};
    virtual void setIsChecked(bool isChecked) { this->isChecked = isChecked; };
};

class SubmitButton : public ButtonElement {
public:
    SubmitButton() : ButtonElement("Submit button", false) {};
    void click() override {
        std::cout << "Submitted!";
    }
};

class NameTextBox : public TextBox {
    SubmitButton *submitButton;
public:
    NameTextBox(SubmitButton *submitButton) : TextBox("Name textbox", true), submitButton(submitButton) {};
    void changeText(const std::string & newValue) override {
        if (newValue.empty()) {
            submitButton->setVisibility(false);
        } else {
            submitButton->setVisibility(true);
        }
        
        TextBox::changeText(newValue);
    }
};

class SpousesNameTextBox : public TextBox {
public:
    SpousesNameTextBox() : TextBox("Spouse's name textbox", false) {};
};

class IsMarriedCheckbox : public CheckBox {
    SpousesNameTextBox *spousesNameTextBox;
public:
    IsMarriedCheckbox(SpousesNameTextBox *spousesNameTextBox) : CheckBox("Is married checkbox", true), spousesNameTextBox(spousesNameTextBox) {};
    void setIsChecked(bool isChecked) override {
        if (isChecked) {
            spousesNameTextBox->setVisibility(true);
        } else {
            spousesNameTextBox->setVisibility(false);
        }
        CheckBox::setIsChecked(isChecked);
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
