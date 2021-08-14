export module Employee;

namespace HR
{
	export enum class title : int
	{
		Manager, SeniorEngineer, Engineer
	};

	export struct Employee
	{
		char firstInitial;
		char secondInitial;
		int employeeNumber;
		int salary;
		title employeeTitle;
	};
}