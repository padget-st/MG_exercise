#pragma once
#include <vector>
#include <optional>
#include <format>

constexpr size_t DEFAULT_WIDTH{ 10 };
constexpr size_t DEFAULT_HEIGHT{ 10 };

constexpr size_t getDefaultWidth()
{
	return DEFAULT_WIDTH * 2;
}

constexpr size_t getDefaultHeight()
{
	return DEFAULT_HEIGHT * 2;
}

template <typename T = int,
	size_t WIDTH = getDefaultWidth(), size_t HEIGHT = getDefaultHeight()>
class Grid
{
public:
	Grid() = default;
	virtual ~Grid() = default;

	Grid(const Grid& src) = default;
	Grid& operator=(const Grid& rhs) = default;

	template <typename E, size_t WIDTH2, size_t HEIGHT2>
	Grid(const Grid<E, WIDTH2, HEIGHT2>& src);

	template <typename E, size_t WIDTH2, size_t HEIGHT2>
	Grid& operator=(const Grid<E, WIDTH2, HEIGHT2>& rhs);
	
	void swap(Grid& other) noexcept;

	std::optional<T>& at(size_t x, size_t y);
	const std::optional<T>& at(size_t x, size_t y) const;

	size_t getWidth() const { return WIDTH; };
	size_t getHeight() const { return HEIGHT; };

	void setData(T data) { m_data = data; }
	T getData() const { return m_data;  }
private:
	void verifyCoordinate(size_t x, size_t y) const;

	std::optional<T> m_cells[WIDTH][HEIGHT];
	T m_data{};
};

template <typename T, size_t WIDTH, size_t HEIGHT>
template <typename E, size_t WIDTH2, size_t HEIGHT2>
Grid<T, WIDTH, HEIGHT>::Grid(const Grid<E, WIDTH2, HEIGHT2>& src)
	: m_data{ static_cast<T>(src.getData()) }
{
	for (size_t i{}; i < WIDTH; i++)
	{
		for (size_t j{}; j < HEIGHT; j++)
		{
			if (i < WIDTH2 && j < HEIGHT2)
			{
				m_cells[i][j] = src.at(i, j);
			}
			else
			{
				m_cells[i][j].reset();
			}
		}
	}
}

template <typename T, size_t WIDTH, size_t HEIGHT>
void Grid<T, WIDTH, HEIGHT>::swap(Grid& other) noexcept
{
	std::swap(m_cells, other.m_cells);
	std::swap(m_data, other.m_data);
}

template <typename T, size_t WIDTH, size_t HEIGHT>
template <typename E, size_t WIDTH2, size_t HEIGHT2>
Grid<T, WIDTH, HEIGHT>& Grid<T, WIDTH, HEIGHT>::operator=(const Grid<E, WIDTH2, HEIGHT2>& rhs)
{
	Grid<T, WIDTH, HEIGHT> temp{ rhs };
	swap(temp);
	return *this;
}

template <typename T, size_t WIDTH, size_t HEIGHT>
void Grid<T, WIDTH, HEIGHT>::verifyCoordinate(size_t x, size_t y) const
{
	if (x >= WIDTH)
	{
		throw std::runtime_error(std::format("{} must be less than {}", x, WIDTH));
	}
	if (y >= HEIGHT)
	{
		throw std::runtime_error(std::format("{} must be less than {}", y, HEIGHT));
	}
}

template <typename T, size_t WIDTH, size_t HEIGHT>
const std::optional<T>& Grid<T, WIDTH, HEIGHT>::at(size_t x, size_t y) const
{
	verifyCoordinate(x, y);
	return m_cells[x][y];
}

template <typename T, size_t WIDTH, size_t HEIGHT>
std::optional<T>& Grid<T, WIDTH, HEIGHT>::at(size_t x, size_t y)
{
	return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}