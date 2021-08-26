#pragma once

#include <string>
#include <string_view>

class SpreadsheetCell
{
public:
	SpreadsheetCell() = default;
	virtual void set(std::string_view value) = 0;
	virtual std::string getString() const = 0;
};
