#include <iostream>
#include "ChainOfResponsibility.h"
#include "Command.h"
#include "Mediator.h"
#include "Observer.h"

void chainOfResponsibility()
{
    StringValidator* emailValidator = new BaseValidator;

    emailValidator
        ->setNext(new NotEmptyValidator)
        ->setNext(new RegexValidator("email address", "^\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$"));

    std::cout << "Checking Emails ---------------\n";
    std::cout << "Input: \n" << emailValidator->validate("") << "\n\n";
    std::cout << "Input: login name\n" << emailValidator->validate("login name") << "\n\n";
    std::cout << "Input: unknown@test.com\n" << emailValidator->validate("unknown@test.com") << "\n\n";

    delete emailValidator;
}

std::string vectorToString(const std::vector<std::string>& v) {
    std::string result = "";
    for (auto& elem : v)
    {
        result.append(elem + ", ");
    }
    return result;
};

void command()
{
    Canvas* canvas = new Canvas;

    Button* addTriangleButton = new Button(new AddShapeCommand("triangle", canvas));
    Button* addSquareButton = new Button(new AddShapeCommand("square", canvas));
    Button* clearButton = new Button(new ClearCommand(canvas));

    addTriangleButton->click();
    std::cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";
    addSquareButton->click();
    addSquareButton->click();
    addTriangleButton->click();
    std::cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";
    clearButton->click();
    std::cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";

    delete canvas;
}

void mediator()
{
    UserInterface* ui = new UserInterface;

    InterfaceElement* elements[] = {
        ui->getNameTextBox(),
        ui->getIsMarriedCheckbox(),
        ui->getSpousesNameTextBox(),
        ui->getSubmitButton(),
    };

    for (auto element : elements) {
        std::cout << element->getDescription() << "\n\n";
    }

    ui->getIsMarriedCheckbox()->setIsChecked(true);

    for (auto element : elements) {
        std::cout << element->getDescription() << "\n";
    }

    delete ui;
}

void observer()
{
    ChatUser* user1 = new ChatUser("Jim");
    ChatUser* user2 = new ChatUser("Barb");
    ChatUser* user3 = new ChatUser("Hannah");

    ChatGroup* group1 = new ChatGroup("Gardening group");
    ChatGroup* group2 = new ChatGroup("Dog-lovers group");

    group1->subscribe(user1);
    group1->subscribe(user2);

    group2->subscribe(user2);
    group2->subscribe(user3);

    group1->publish("Special sale on gardening supplies!");
    group2->publish("It's national dog day everyone!");

    delete user1;
    delete user2;
    delete user3;
    delete group1;
    delete group2;
}

int main()
{
    observer();
}