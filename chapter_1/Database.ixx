export module Database;
import RealEmployee;
#include "ImportSTDUnits.h"

namespace Records
{
	constexpr int firstEmployeeNumber{ 1'000 };

	export class Database
	{
	private:
		std::vector<Employee> m_employees;
		int m_nextEmployeeNumber{ firstEmployeeNumber };
	public:
		Employee& addEmployee(const std::string& firstName, const std::string& lastName);
		Employee& getEmployee(const int employeeNumber);
		Employee& getEmployee(const std::string& firstName, const std::string& lastName);

		void displayAll() const;
		void displayCurrent() const;
		void displayFormer() const;
	};


	Employee& Database::addEmployee(const std::string& firstName, const std::string& lastName)
	{
		Employee tempEmployee{ firstName, lastName };
		tempEmployee.setEmployeeNumber(m_nextEmployeeNumber++);
		tempEmployee.hire();
		m_employees.push_back(tempEmployee);
		return m_employees.back();
	}

	Employee& Database::getEmployee(const int employeeNumber)
	{
		for (auto& employee : m_employees)
		{
			if (employee.getEmployeeNumber() == employeeNumber)
			{
				return employee;
			}
			throw std::logic_error("No employee found");
		}
	}

	Employee& Database::getEmployee(const std::string& firstName, const std::string& lastName)
	{
		for (auto& employee : m_employees)
		{
			if (employee.getFirstName() == firstName
				&& employee.getLastName() == lastName)
			{
				return employee;
			}
			throw std::logic_error("No employee found");
		}
	}

	void Database::displayAll() const
	{
		for (const auto& employee : m_employees) { employee.display(); }
	}

	void Database::displayCurrent() const
	{
		for (const auto& employee : m_employees)
		{
			if (employee.isHired()) { employee.display(); }
		}
	}

	void Database::displayFormer() const
	{
		for (const auto& employee : m_employees)
		{
			if (!employee.isHired()) { employee.display(); }
		}
	}
}
