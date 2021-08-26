#pragma once
#include "Employee.h"

namespace HR
{
	class Manager : public Employee
	{
	public:
		using Employee::Employee;

		Manager(const Employee& employee) noexcept
			: Employee(employee)
		{
			
		}

		virtual ~Manager() = default;

		std::string toString() const override
		{
			std::string temp{ Employee::toString() };
			temp += "::Manager";
			return temp;
		}
	};
}
