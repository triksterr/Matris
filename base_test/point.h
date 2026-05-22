#pragma once
// file: point.h

// Класс двумерной точки (X, Y) - пары int
class Point
{
public:
	int x; 
	int y;

	Point() : x(0), y(0) {}

	Point(int x=0, int y=0) : x(x), y(y) {}
	
	// Копирующий конструктор
	Point(const Point& other) : x(other.x), y(other.y) {}

	// Присваивание копированием
	Point& operator=(const Point& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	// Перемещающий конструктор
	Point(Point&& other) noexcept : x(other.x), y(other.y) {}

	// Присваивание перемещением
	Point& operator=(Point&& other) noexcept
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	// Деструктор
	~Point() = default;

	// Операторы сравнения
	bool operator==(const Point& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Point& other) const
	{
		return x != other.x || y != other.y;
	}
};

