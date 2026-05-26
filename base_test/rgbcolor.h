#pragma once
// file: rgbcolor.h

// Цвет в формате RGB
class RGBcolor
{
public:
	int r = 0;
	int g = 0;
	int b = 0;

	// default конструктор - ?
	//RGBcolor() = default;

	// конструктор
	RGBcolor(int r, int g, int b) : r(r), g(g), b(b) {}

	// copy конструктор
	RGBcolor(const RGBcolor& other) : r(other.r), g(other.g), b(other.b) {}

	// copy присваивание
	RGBcolor& operator=(const RGBcolor& other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		return *this;
	}

	// move конструктор
	RGBcolor(RGBcolor&& other) noexcept : r(other.r), g(other.g), b(other.b) {}

	// move присваивание
	RGBcolor& operator=(RGBcolor&& other) noexcept
	{
		r = other.r;
		g = other.g;
		b = other.b;
		return *this;
	}

	// деструктор
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

