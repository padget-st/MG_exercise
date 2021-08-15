#include <iostream>
#include <string_view>

class Employee;

/**
* Implements the basic functionality for storing and
* retrieving employees
*/
class Database
{
public:
    /**
    * @throws no exceptions
    * @return reference to an existing employee, if stored
    */
    Employee& addEmployee(const std::string& firstName,
        const std::string& lastName);
    /**
    * @param employeeNumber must be >= 0
    * @throws an logic_error if employeeNumber <=0 and 
    * wrong_employee_exception if not found
    */
    Employee& getEmployee(int employeeNumber);
    /**
    * @throws wrong_employee_exception if not found
    */
    Employee& getEmployee(const std::string& firstName,
        const std::string& lastName);
};

class XrayController
{
public:
    double getXrayCurrent() const;
    void setXrayCurrent(double currentValue);

    void setXrayZeroCurrent();

    std::string_view getXraySourceType() const;
    void setXraySourceType(std::string_view sourceType);

private:
    double m_XrayCurrent;
    std::string m_sourceType;
};

Employee& Database::getEmployee(int employeeNumber)
{
    for (auto& employee : m_employees)
    {
        if (employee.getEmployeeNumber() == employeeNumber)
        {
            return employee;
        }
    }
    throw std::logic_error("No employee found");
}

int main()
{
    std::cout << "Hello World!\n";
}
