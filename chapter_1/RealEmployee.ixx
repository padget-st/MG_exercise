export module RealEmployee;
#include "ImportSTDUnits.h"

namespace Records
{
	constexpr int defaultStartingSalary{ 30'000 };
	export constexpr int defaultRaiseAndDemeritAmount{ 1'000 };

	export class Employee
	{
	private:
		std::string m_firstName;
		std::string m_lastName;
		int m_employeeNumber{ -1 };
		int m_salary{ defaultStartingSalary };
		bool m_hired{ false };
	public:
		Employee(const std::string& firstName, const std::string& lastName);

		void promote(int raiseAmount = defaultRaiseAndDemeritAmount);
		void demote(int demeritAmount = defaultRaiseAndDemeritAmount);
		void hire();
		void fire();
		void display() const;

		void setFirstName(const std::string& firstName);
		const std::string& getFirstName() const;

		void setLastName(const std::string& lastName);
		const std::string& getLastName() const;

		void setEmployeeNumber(const int employeeNumber);
		int getEmployeeNumber() const;

		void setSalary(int newSalary);
		int getSalary() const;

		bool isHired() const;
	};



	Employee::Employee(const std::string& firstName, const std::string& lastName)
		: m_firstName{ firstName }, m_lastName{ lastName }
	{}

	void Employee::promote(int raiseAmount)
	{
		setSalary(getSalary() + raiseAmount);
	}

	void Employee::demote(int demeritAmount)
	{
		setSalary(getSalary() - demeritAmount);
	}

	void Employee::hire() { m_hired = true; }
	void Employee::fire() { m_hired = false; }

	void Employee::display() const
	{
		std::cout << std::format("Employee: {}, {}", getLastName(), getFirstName()) << std::endl;
		std::cout << "----------------------------\n";
		std::cout << (isHired() ? "Current employee" : "Former employee") << std::endl;
		std::cout << std::format("Employee's number: {}", getEmployeeNumber()) << std::endl;
		std::cout << std::format("Salary: ${}", getSalary()) << std::endl;
		std::cout << std::endl;
	}

	void Employee::setFirstName(const std::string& firstName)
	{
		m_firstName = firstName;
	}

	const std::string& Employee::getFirstName() const
	{
		return m_firstName;
	}

	void Employee::setLastName(const std::string& lastName)
	{
		m_lastName = lastName;
	}

	const std::string& Employee::getLastName() const
	{
		return m_lastName;
	}

	void Employee::setEmployeeNumber(const int employeeNumber)
	{
		m_employeeNumber = employeeNumber;
	}

	int Employee::getEmployeeNumber() const
	{
		return m_employeeNumber;
	}

	void Employee::setSalary(const int newSalary)
	{
		m_salary = newSalary;
	}

	int Employee::getSalary() const
	{
		return m_salary;
	}

	bool Employee::isHired() const
	{
		return m_hired;
	}
}
