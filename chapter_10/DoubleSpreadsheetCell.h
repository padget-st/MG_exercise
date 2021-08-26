#pragma once

#include <string>
#include <string_view>
#include <optional>
#include <charconv>
#include "SpreadsheetCell.h"

class DoubleSpreadsheetCell : public SpreadsheetCell
{
public:
	virtual void set(double value);
	void set(std::string_view value) override;
	std::string getString() const override;
private:
	static std::string doubleToString(double value);
	static double stringToDouble(std::string_view value);
	std::optional<double> m_value;
};
