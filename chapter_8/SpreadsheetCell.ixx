module;

#include <string>
#include <string_view>
#include <charconv>

export module SpreadsheetCell_module;

export class SpreadsheetCell
{
private:
	double m_value{ 0 };

	static std::string doubleToString(double value);
	static double stringToDouble(std::string_view value);

public:
	SpreadsheetCell() = default;
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(std::string_view initialValue);
	SpreadsheetCell(const SpreadsheetCell & src);

	SpreadsheetCell& operator=(const SpreadsheetCell & rhSpreadsheetCell);

	void setValue(double value);
	double getValue() const;

	void setString(std::string_view value);
	std::string getString() const;
};

SpreadsheetCell::SpreadsheetCell(double initialValue)
	: m_value{ initialValue }
{
}

SpreadsheetCell::SpreadsheetCell(std::string_view initialValue)
	: m_value{ stringToDouble(initialValue) }
{
}

SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& src)
	: m_value{ src.m_value }
{
}

SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
{
	if (this == &rhs) {
		return *this;
	}
	m_value = rhs.m_value;
	return *this;
}

void SpreadsheetCell::setValue(double value)
{
	m_value = value;
}

double SpreadsheetCell::getValue() const
{
	return m_value;
}

void SpreadsheetCell::setString(std::string_view value)
{
	m_value = stringToDouble(value);
}

std::string SpreadsheetCell::getString() const
{
	return doubleToString(m_value);
}

std::string SpreadsheetCell::doubleToString(double value)
{
	return std::to_string(value);
}

double SpreadsheetCell::stringToDouble(std::string_view value)
{
	double number{ 0 };
	std::from_chars(value.data(), value.data() + value.size(), number);
	return number;
}
