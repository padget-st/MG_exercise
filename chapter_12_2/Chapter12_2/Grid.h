#pragma once
#include <vector>
#include <optional>
#include <format>

template <typename T>
class Grid
{
public:
	explicit Grid(size_t width = DefaultWidth, size_t height = DefaultHeight);
	virtual ~Grid() = default;

	Grid(const Grid& src) = default;
	Grid& operator=(const Grid& rhs) = default;

	Grid(Grid&& src) = default;
	Grid& operator=(Grid&& src) = default;
	
	std::optional<T>& at(size_t x, size_t y);
	const std::optional<T>& at(size_t x, size_t y) const;

	static const size_t DefaultWidth{ 10 };
	static const size_t DefaultHeight{ 10 };
private:
	void verifyCoordinate(size_t x, size_t y) const;

	std::vector<std::vector<std::optional<T>>> m_cells;
	size_t m_width{}, m_height{};
};

template <typename T>
Grid<T>::Grid(size_t width, size_t height)
	: m_width{ width }, m_height{ height }
{
	m_cells.resize(width);
	for (auto& elem : m_cells)
	{
		elem.resize(height);
	}
}

template <typename T>
void Grid<T>::verifyCoordinate(size_t x, size_t y) const
{
	if (x >= m_width)
	{
		throw std::runtime_error(std::format("{} must be less than {}", x, m_width));
	}
	if (y >= m_height)
	{
		throw std::runtime_error(std::format("{} must be less than {}", y, m_height));
	}
}

template <typename T>
const std::optional<T>& Grid<T>::at(size_t x, size_t y) const
{
	verifyCoordinate(x, y);
	return m_cells[x][y];
}

template <typename T>
std::optional<T>& Grid<T>::at(size_t x, size_t y)
{
	return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}