#pragma once
// file: rgbcolor.h

// Цвет в формате RGB
class RGBcolor
{
public:
	int r;
	int g;
	int b;

	// Конструктор по умолчанию
	RGBcolor() : r(0), g(0), b(0) {}

	// Конструктор
	RGBcolor(int r, int g, int b) : r(r), g(g), b(b) {}

	// Конструктор копирования
	RGBcolor(const RGBcolor& other) : r(other.r), g(other.g), b(other.b) {}

	// Оператор присваивания копированием
	RGBcolor& operator=(const RGBcolor& other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		return *this;
	}

	// Конструктор перемещения
	RGBcolor(RGBcolor&& other) noexcept : r(other.r), g(other.g), b(other.b) {}

	// Оператор присваивания перемещением
	RGBcolor& operator=(RGBcolor&& other) noexcept
	{
		r = other.r;
		g = other.g;
		b = other.b;
		return *this;
	}

	// Деструктор
	~RGBcolor() = default;

	// Операторы сравнения
	bool operator==(const RGBcolor& other) const
	{
		return r == other.r && g == other.g && b == other.b;
	}

	bool operator!=(const RGBcolor& other) const
	{
		return r != other.r || g != other.g || b != other.b;
	}
};

