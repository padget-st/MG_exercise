module;

#include <cstddef>
#include <exception>
#include <format>

export module Spreadsheet_module;

export import SpreadsheetCell_module;

export class Spreadsheet
{
private:
	size_t m_width{};
	size_t m_height{};
	SpreadsheetCell** m_cells{ nullptr };
	bool verifyCoordinate(size_t x, size_t y) const;
public:
	Spreadsheet(size_t width, size_t height);
	Spreadsheet(const Spreadsheet& source);

	~Spreadsheet();

	Spreadsheet& operator=(const Spreadsheet& rhSpreadsheet);
	void swap(Spreadsheet& other) noexcept;

	void setCellAt(size_t x, size_t y, const SpreadsheetCell& cell);
	SpreadsheetCell& getCellAt(size_t x, size_t y);
};

void Spreadsheet::swap(Spreadsheet& other) noexcept
{
	std::swap(m_width, other.m_width);
	std::swap(m_height, other.m_height);
	std::swap(m_cells, other.m_cells);
}

Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhSpreadsheet) noexcept
{
	Spreadsheet temp{ rhSpreadsheet };
	this->swap(temp);
	return *this;
}

Spreadsheet::Spreadsheet(size_t width, size_t height)
	: m_width{width}, m_height{height}
{
	m_cells = new SpreadsheetCell*[m_width];
	for (size_t i{}; i < m_width; i++)
	{
		m_cells[i] = new SpreadsheetCell[m_height];
	}
}

Spreadsheet::Spreadsheet(const Spreadsheet& source)
	: Spreadsheet{source.m_width, source.m_height}
{
	for (size_t i{}; i < m_width; i++)
	{
		for (size_t j{}; j < m_height; j++)
		{
			m_cells[i][j] = source.m_cells[i][j];
		}
	}
}

Spreadsheet::~Spreadsheet()
{
	for (size_t i{}; i < m_width; i++)
	{
		delete[] m_cells[i];
	}
	delete[] m_cells;
	m_cells = nullptr;
}

bool Spreadsheet::verifyCoordinate(size_t x, size_t y) const
{
	if (x >= m_width)
	{
		throw std::runtime_error(std::format("{} must be less than {}", x, m_width));
	}
	if (x >= m_height)
	{
		throw std::runtime_error(std::format("{} must be less than {}", y, m_height));
	}
}

void Spreadsheet::setCellAt(size_t x, size_t y, const SpreadsheetCell& cell)
{
	verifyCoordinate(x, y);
	m_cells[x][y] = cell;
}

SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y)
{
	verifyCoordinate(x, y);
	return m_cells[x][y];
}

export void swap(Spreadsheet& lhSpreadsheet, Spreadsheet& rhSpreadsheet) noexcept
{
	lhSpreadsheet.swap(rhSpreadsheet);
}