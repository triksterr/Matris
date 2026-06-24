#pragma once
// file: point.h

// Алиас класса Point для хранения размеров
// Size: w, h
using Size = Point;

// Класс двумерной точки (X, Y) - пары int
class Point
{
public:
	union
	{
		int x = 0;
		int w; // ширина при обращении через алиас Size
		int width;
	};

	union
	{
		int y = 0;
		int h; // высота при обращении через алиас Size
		int height;
	};

	//Point() = default;

	Point(int x=0, int y=0) : x(x), y(y) {}
	
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

