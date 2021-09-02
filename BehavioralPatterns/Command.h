#pragma once
#include <iostream>
#include <vector>
#include <string>

class Canvas {
    std::vector<std::string> shapes;
public:
    void addShape(const std::string& newShape) {
        shapes.push_back(newShape);
    };
    void clearAll() {
        shapes.clear();
    };
    std::vector<std::string> getShapes() { return shapes; };
};

class Command
{
public:
    virtual ~Command() {};
    virtual void execute() = 0;
};

class AddShapeCommand : public Command
{
private:
    std::string m_shapeName{};
    Canvas* m_canvas{ nullptr };
public:
    AddShapeCommand(const std::string& shapeName, Canvas* canvas)
        : m_shapeName{shapeName}, m_canvas{canvas}
    {};

    void execute() override
    {
        m_canvas->addShape(m_shapeName);
    }
};

class ClearCommand : public Command
{
private:
    Canvas* m_canvas;
public:
    ClearCommand(Canvas* canvas) : m_canvas{ canvas }
    {};

    void execute() override
    {
        m_canvas->clearAll();
    }
};

class Button {
private:
    Command* m_command;
public:
    Button(Command* command) : m_command{ command } {}

    void click()
    {
        m_command->execute();
    }
};