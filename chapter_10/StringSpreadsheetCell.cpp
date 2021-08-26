#include "StringSpreadsheetCell.h"

void StringSpreadsheetCell::set(std::string_view value)
{
	m_value = value;
}

std::string StringSpreadsheetCell::getString() const
{
	return m_value.value_or("");
}