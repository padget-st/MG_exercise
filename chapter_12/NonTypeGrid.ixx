export module NonTypeGrid_module;

import <optional>;
import <stdexcept>;
import <iostream>;

export template <typename T = int, size_t WIDTH = 10, size_t HEIGHT = 10>
class NonTypeGrid
{
private:
	std::optional<T> m_cells[WIDTH][HEIGHT];
	void verifyCoordinate(size_t x, size_t y) const;
public:
	NonTypeGrid() = default;
	virtual ~NonTypeGrid() = default;

	NonTypeGrid(const NonTypeGrid&) = default;
	NonTypeGrid& operator=(const NonTypeGrid&) = default;

	void swap(NonTypeGrid&) noexcept;
	NonTypeGrid(NonTypeGrid&&) noexcept;
	NonTypeGrid& operator=(NonTypeGrid&&) noexcept;

	std::optional<T>& at(size_t, size_t);
	const std::optional<T>& at(size_t, size_t) const;

	size_t getWidth() const { return WIDTH; }
	size_t getHeight() const { return HEIGHT; }
};

template <typename T, size_t WIDTH, size_t HEIGHT>
void NonTypeGrid<T, WIDTH, HEIGHT>::swap(NonTypeGrid& grid) noexcept
{
	std::swap(m_cells, grid.m_cells);
}

template <typename T, size_t WIDTH, size_t HEIGHT>
NonTypeGrid<T, WIDTH, HEIGHT>::NonTypeGrid(NonTypeGrid&& grid) noexcept
{
	swap(grid);
}

template <typename T, size_t WIDTH, size_t HEIGHT>
NonTypeGrid<T, WIDTH, HEIGHT>& NonTypeGrid<T, WIDTH, HEIGHT>::operator=(NonTypeGrid&& grid) noexcept
{
	swap(grid);
	return *this;
}

template <typename T, size_t WIDTH, size_t HEIGHT>
void NonTypeGrid<T, WIDTH, HEIGHT>::verifyCoordinate(size_t x, size_t y) const
{
	if (x >= WIDTH || y >= HEIGHT)
	{
		throw std::runtime_error("Coordinates: out of bounds");
	}
} 

template <typename T, size_t WIDTH, size_t HEIGHT>
const std::optional<T>& NonTypeGrid<T, WIDTH, HEIGHT>::at(size_t x, size_t y) const
{
	verifyCoordinate(x, y);
	return m_cells[x][y];
}

template <typename T, size_t WIDTH, size_t HEIGHT>
std::optional<T>& NonTypeGrid<T, WIDTH, HEIGHT>::at(size_t x, size_t y)
{
	return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}

