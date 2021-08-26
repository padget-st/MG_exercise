export module manager_module;

import employee_module;

export namespace HR
{
	class Manager : public Employee
	{
	public:
		using Employee::Employee;
	};
}