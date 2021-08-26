#pragma once

#include <string>
#include <string_view>
#include <optional>
#include "SpreadsheetCell.h"

class StringSpreadsheetCell : public SpreadsheetCell
{
public:
	void set(std::string_view value) override;
	std::string getString() const override;
private:
	std::optional<std::string> m_value;
};
