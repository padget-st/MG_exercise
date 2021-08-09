#include <iostream>
#include <format>
import Employee;

int main()
{
    Employee employee;
    employee.firstInitial = 'J';
    employee.secondInitial = 'D';
    employee.employeeNumber = 43;
    employee.salary = 3000;

    std::cout << std::format("Employee: {}{}", employee.firstInitial, employee.secondInitial) << "\n";
    std::cout << std::format("Number: {}", employee.employeeNumber) << "\n";
    std::cout << std::format("Salary: {}", employee.salary);
}
