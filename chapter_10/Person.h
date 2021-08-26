#pragma once
#include <string>
#include <format>

namespace HR
{
	class Person
	{
	private:
	private:
		std::string m_firstName{};
		std::string m_lastName{};
		std::string m_initials{};

		static std::string setInitialsFromNames(const std::string& firstName,
			const std::string& lastName)
		{
			std::string tempInitials{};
			tempInitials += firstName[0];
			tempInitials += lastName[0];
			return tempInitials;
		}

	public:
		Person(std::string firstName, std::string lastName)
			: Person{ std::move(firstName), std::move(lastName),
			std::move(setInitialsFromNames(firstName, lastName)) }
		{}

		Person() = default;

		Person(std::string firstName, std::string lastName, std::string initials)
			: m_firstName{ std::move(firstName) }
			, m_lastName{ std::move(lastName) }
			, m_initials{ std::move(initials) }
		{
		}

		virtual ~Person() = default; // A virtual destructor

		virtual std::string toString() const
		{
			std::string temp{"Person"};
			return temp;
		}

		virtual const std::string& getFirstName() const { return m_firstName; }
		virtual void setFirstName(std::string firstName) { m_firstName = std::move(firstName); }

		virtual const std::string& getLastName() const { return m_lastName; }
		virtual void setLastName(std::string lastName) { m_lastName = std::move(lastName); }

		virtual const std::string& getInitials() const { return m_initials; }
		virtual void setInitials(std::string initials) { m_initials = std::move(initials); }
	};
}
