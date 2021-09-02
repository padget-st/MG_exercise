#pragma once
#include <iostream>

class Mediator {
public:
    virtual void mediate(const std::string& event) = 0;
};

class InterfaceElement {
protected:
    Mediator* mediator;
    std::string name;
    bool isVisible = true;
public:
    InterfaceElement(const std::string& name, bool isVisible, Mediator* mediator) : name(name), isVisible(isVisible), mediator(mediator) {};
    void setVisibility(bool isVisible) { this->isVisible = isVisible; };
    std::string getDescription() {
        return isVisible
            ? name + " is visible"
            : name + " is NOT visible";
    }
};

class ButtonElement : public InterfaceElement {
public:
    ButtonElement(const std::string& name, bool isVisible, Mediator* mediator) : InterfaceElement(name, isVisible, mediator) {};
    virtual ~ButtonElement() {};
    virtual void click() {
        mediator->mediate(name + " clicked");
    };
};

class TextBox : public InterfaceElement {
    std::string textValue = "";
public:
    TextBox(const std::string& name, bool isVisible, Mediator* mediator) : InterfaceElement(name, isVisible, mediator) {};
    virtual ~TextBox() {};
    virtual void changeText(const std::string& newValue) {
        textValue = newValue;
        if (newValue.empty()) {
            mediator->mediate(name + " empty");
        }
        else {
            mediator->mediate(name + " not empty");
        }
    };
};

class CheckBox : public InterfaceElement {
    bool isChecked = false;
public:
    CheckBox(const std::string& name, bool isVisible, Mediator* mediator) : InterfaceElement(name, isVisible, mediator) {};
    virtual ~CheckBox() {};
    virtual void setIsChecked(bool isChecked) {
        this->isChecked = isChecked;

        if (isChecked) {
            mediator->mediate(name + " is checked");
        }
        else {
            mediator->mediate(name + " is unchecked");
        }
    };
};

class UserInterface : public Mediator {
    TextBox* nameTextBox;
    CheckBox* isMarriedCheckbox;
    TextBox* spousesNameTextBox;
    ButtonElement* submitButton;
public:
    UserInterface() {
        nameTextBox = new TextBox("Name textbox", true, this);
        isMarriedCheckbox = new CheckBox("Is married checkbox", true, this);
        spousesNameTextBox = new TextBox("Spouse's name textbox", false, this);
        submitButton = new ButtonElement("Submit button", false, this);
    }
    ~UserInterface() {
        delete nameTextBox;
        delete isMarriedCheckbox;
        delete spousesNameTextBox;
        delete submitButton;
    }
    void mediate(const std::string& event) override {
        std::cout << "Mediating event: " << event << "...\n";

        if (event == "Name textbox is empty") {
            submitButton->setVisibility(false);
        }
        else if (event == "Name textbox is not empty") {
            submitButton->setVisibility(true);
        }
        else if (event == "Is married checkbox is checked") {
            spousesNameTextBox->setVisibility(true);
        }
        else if (event == "Is married checkbox is unchecked") {
            spousesNameTextBox->setVisibility(false);
        }
        else if (event == "Submit button clicked") {
            std::cout << "Submitted!\n";
        }
        else {
            std::cout << "Unrecognized event!";
        }
    }
    TextBox* getNameTextBox() { return nameTextBox; };
    CheckBox* getIsMarriedCheckbox() { return isMarriedCheckbox; };
    TextBox* getSpousesNameTextBox() { return spousesNameTextBox; };
    ButtonElement* getSubmitButton() { return submitButton; };
};

