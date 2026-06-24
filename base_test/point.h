#pragma once
// file: point.h

// Алиас класса Point для хранения размеров
// Size: w, h (width, height)
using Size = Point;

// Класс двумерной точки (X, Y) - пары int
class Point
{
public:
	union
	{
		int x = 0; // координата X
		int w; // ширина (через алиас Size)
		int width; // ширина (через алиас Size)
	};

	union
	{
		int y = 0; // координата Y
		int h; // высота (через алиас Size)
		int height; // высота (через алиас Size)
	};

	Point(int x = 0, int y = 0) : x(x), y(y) {}
	
	// copy конструктор
	Point(const Point& other) : x(other.x), y(other.y) {}

	// copy присваивание
	Point& operator=(const Point& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	// move конструктор
	Point(Point&& other) noexcept : x(other.x), y(other.y) {}

	// move присваивание
	Point& operator=(Point&& other) noexcept
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	// деструктор
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

