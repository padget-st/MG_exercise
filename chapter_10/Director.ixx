export module director_module;

import employee_module;

export namespace HR
{
	class Director : public Employee
	{
	public:
		using Employee::Employee;
	};
}


