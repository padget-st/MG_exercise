#include <iostream>
#include <format>
#include <compare>
#include <array>
#include <optional>
#include <initializer_list>
#include "ImportSTDUnits.h"
import Employee;
import airline_ticket;
//import RealEmployee;
//import HRHelper;

/*[[nodiscard("Error_code_returns")]]*/ int returnCode() noexcept
{
    return 1;
}

/*[[deprecated("dull_function")]]*/ void printFuncName() noexcept
{
    std::cout << std::format("My name is {}", __func__) << '\n';
}

std::optional<int> returnOptId(bool enableId)
{
    if (enableId)
    {
        return 10;
    }
    return std::nullopt;
}

auto initListAvg(std::initializer_list<int> list)
{
    int total{};
    for (auto& elem : list)
    {
        total += elem;
    }
    return total / list.size();
}

int main()
{
    /*Employee employee;
    employee.firstInitial = 'J';
    employee.secondInitial = 'D';
    employee.employeeNumber = 43;
    employee.salary = 3000;

    std::cout << std::format("Employee: {}{}", employee.firstInitial, employee.secondInitial) << "\n";
    std::cout << std::format("Number: {}", employee.employeeNumber) << "\n";
    std::cout << std::format("Salary: {}", employee.salary) << "\n";

    int a{ 10 };
    std::strong_ordering result{ a <=> 5 };
    if (std::is_lt(result)) { std::cout << "less\n"; }
    if (std::is_eq(result)) { std::cout << "equal\n"; }
    if (std::is_gt(result)) { std::cout << "greater\n"; }

    if (auto res{ (a <=> 15) }; std::is_eq(res))
        [[unlikely]] {
            std::cout << "equal\n";
    }
    else
        [[likely]] {
            std::cout << "not equal\n";
    }

    printFuncName();
    returnCode();

    int arr[5]{};
    std::cout << "array's size: " << std::size(arr) << '\n';
    std::cout << "old style size: " << (sizeof(arr) / sizeof(arr[0])) << '\n';

    auto data1{ returnOptId(true) };
    auto data2{ returnOptId(false) };

    std::cout << "data1 has value " << data1.value() << '\n';
    if (!data2)
    {
        std::cout << "data2 hasn't any value, but returns " << data2.value_or(1) << '\n';
    }

    std::array<int, 3> arrayInt{ 1, 3, 5 };
    auto [q, w, e] {arrayInt};
    std::cout << std::format("q = {}, w = {}, e = {}\n", q, w, e);

    for (std::array<int, 3> for_arr{ 2, 4, 6 }; auto & elem : for_arr)
    {
        std::cout << elem << '\n';
    }

    std::cout << initListAvg({ 1, 2, 3, 4, 5 }) << '\n';

    Employee empl
    {
        .firstInitial{'A'},
        .secondInitial{'F'},
        .employeeNumber{100},
        .salary{100'000}
    };
    std::cout << empl.secondInitial << " " << empl.salary << "\n";

    Records::Employee empl2("John", "Doe");
    empl2.promote();
    empl2.display();*/
    
    //Records::HRHelper hr;
    //hr.start();

    /*HR::Employee empl1
    {
        .firstInitial{'J'},
        .secondInitial{'D'},
        .employeeNumber{43},
        .salary{4000},
        .employeeTitle{HR::title::Engineer}
    };

    switch (empl1.employeeTitle)
    {
    case HR::title::Manager:
        std::cout << "Manager\n";
        break;
    case HR::title::SeniorEngineer:
        std::cout << "Senior Engineer\n";
        break;
    case HR::title::Engineer:
        std::cout << "Engineer\n";
        break;
    default:
        std::cout << "Unknown title\n";
    }

    HR::Employee empl2{ 'A', 'A', 45, 2000, HR::title::SeniorEngineer };
    HR::Employee empl3{ 'F', 'S', 46, 2500, HR::title::Manager };

    std::array<HR::Employee, 3> empl_arr;
    empl_arr[0] = empl1;
    empl_arr[1] = empl2;
    empl_arr[2] = empl3;

    std::vector<HR::Employee> empl_v;
    empl_v.push_back(empl1);
    empl_v.push_back(empl2);
    empl_v.push_back(empl3);*/

    //for (const auto& employee : empl_v /*empl_arr*/)
    /*{
        std::cout << std::format("Employee: {}{}, number: {}, salary: {}\n",
            employee.firstInitial, employee.secondInitial, employee.employeeNumber, employee.salary);
    }*/

    AirlineTicket ticket;
    ticket.setNumberOfMiles(1'000);
    ticket.setPassengerName("Boris Johnson");

    std::cout << std::format("Passenger's name: {}, miles: {}, has elite status: {}",
        ticket.getPassengerName(), ticket.getNumberOfMiles(), ticket.hasEliteSuperRewardsStatus());
}
