#include "DoubleSpreadsheetCell.h"

void DoubleSpreadsheetCell::set(double value)
{
	m_value = value;
}

void DoubleSpreadsheetCell::set(std::string_view value)
{
	m_value = stringToDouble(value);
}

std::string DoubleSpreadsheetCell::getString() const
{
	return (m_value.has_value() ? doubleToString(m_value.value()) : "");
}

std::string DoubleSpreadsheetCell::doubleToString(double value)
{
	return std::to_string(value);
}

double DoubleSpreadsheetCell::stringToDouble(std::string_view value)
{
	double number{};
	std::from_chars(value.data(), value.data() + value.size(), number, std::chars_format::fixed);
	return number;
}