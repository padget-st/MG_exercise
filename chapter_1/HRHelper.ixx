export module HRHelper;
#include "ImportSTDUnits.h"
import RealEmployee;
import Database;

namespace Records
{
	export class HRHelper
	{
	private:
		Database m_db{};

		int displayMenu() const;
		void doHire();
		void doFire();
		void doPromote();
	public:
		void start();
	};


	int HRHelper::displayMenu() const
	{
		int selection{};
		std::cout << std::endl;
		std::cout << "Employee Database\n";
		std::cout << "-----------------\n";
		std::cout << "1) Hire a new employee\n";
		std::cout << "2) Fire an employee\n";
		std::cout << "3) Promote an employee\n";
		std::cout << "4) List all employees\n";
		std::cout << "5) List all current employees\n";
		std::cout << "6) List all former employees\n";
		std::cout << "7) Quit\n";
		std::cout << std::endl;
		std::cout << "--->";
		std::cin >> selection;
		return selection;
	}

	void HRHelper::doHire()
	{
		std::string firstName, lastName;

		std::cout << "First name? ";
		std::cin >> firstName;

		std::cout << "Last name? ";
		std::cin >> lastName;

		auto& employee{ m_db.addEmployee(firstName, lastName) };
		std::cout << std::format("Hired employee {} {} with employee number {}.",
			firstName, lastName, employee.getEmployeeNumber()) << std::endl;
	}

	void HRHelper::doFire()
	{
		int employeeNumber{};
		
		std::cout << "Employee number? ";
		std::cin >> employeeNumber;

		try
		{
			auto& employee{ m_db.getEmployee(employeeNumber) };
			employee.fire();
			std::cout << std::format("Employee {} terminated.\n", employeeNumber);
		}
		catch (const std::logic_error& exception)
		{
			std::cerr << std::format("Unable to terminate employee: {}\n",
				exception.what());
		}
	}

	void HRHelper::doPromote()
	{
		int employeeNumber{}, raiseAmount{};

		std::cout << "Employee number? ";
		std::cin >> employeeNumber;

		std::cout << "How much of a raise? ";
		std::cin >> raiseAmount;

		try
		{
			auto& employee{ m_db.getEmployee(employeeNumber) };
			employee.promote(raiseAmount);
		}
		catch (const std::logic_error& exception)
		{
			std::cerr << std::format("Unable to promote employee: {}\n",
				exception.what());
		}
	}

	void HRHelper::start()
	{
		bool done{ false };
		while (!done)
		{
			int selection{ displayMenu() };
			switch (selection)
			{
			case 0:
				done = true;
				break;
			case 1:
				doHire();
				break;
			case 2:
				doFire();
			case 3:
				doPromote();
				break;
			case 4:
				m_db.displayAll();
				break;
			case 5:
				m_db.displayCurrent();
				break;
			case 6:
				m_db.displayFormer();
				break;
			default:
				std::cerr << "Unknown command.\n";
				break;
			}
		}
	}

}