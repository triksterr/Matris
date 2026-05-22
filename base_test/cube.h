#pragma once
// file: cube.h

#include "RGBcolor.h"

// Kубик
class cube
{

	// конструктор по умолчанию
	cube() : digit(0), color({ 0,0,0 }), type(0)
	{}

	// конструктор
	cube(int digit = 0, RGBcolor color = { 0,0,0 }, int type = 0) : digit(digit), color(color), type(type)
	{}

	//! TODO Получать цвет из фигуры - в конструкторе, вызываемом из фигуры - с учетом правил раунда

	// деструктор
	~cube() = default;

	void setDigit(int digit)
	{
		this->digit = digit;
	}

	void setColor(int r, int g, int b)
	{
		color = { r, g, b };
	}
	void setColor(RGBcolor color)
	{
		this->color = color;
	}

	void setType(int type)
	{
		this->type = type;
	}

	int getDigit() const
	{
		return digit;
	}

	RGBcolor getColor() const
	{
		return color;
	}

	int getType() const
	{
		return type;
	}

private:
	int digit; //! IDEA число в кубике - float? - для вариантов: 2.5  0.7  и т.п. ????
	RGBcolor color; // цвет
	int type; // тип кубика: обычный = 0, шарик (*), "пушка", "ракетка", ...
	//bool visible; // видимость - ??? - в тип?
	//bool deleted; // уничтожен - пометка о необходимости удалить - ???
};
