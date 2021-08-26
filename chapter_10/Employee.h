#pragma once
#include "Person.h"

namespace HR
{
	class Employee : public Person
	{
	private:
		int m_id{};
	public:
		Employee(std::string firstName, std::string lastName, int employeeID)
			: Person(std::move(firstName), std::move(lastName)), m_id{ employeeID }
		{}

		virtual ~Employee() = default;

		std::string toString() const override
		{
			std::string temp{ Person::toString() };
			temp += "::Employee";
			return temp;
		}

		virtual int getID() const { return m_id; }
		virtual void setID(int newID) { m_id = newID; }
	};
}
