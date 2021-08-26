#pragma once
#include "Employee.h"

namespace HR
{
	class Director : public Employee
	{
	public:
		using Employee::Employee;
		virtual ~Director() = default;

		std::string toString() const override
		{
			std::string temp{ Employee::toString() };
			temp += "::Director";
			return temp;
		}
	};
}
