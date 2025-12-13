#pragma once
// @file: types.h

#include <functional>

// Типы кубиков
// 0 - обычный числовой кубик
// 1 - кубик со знаком операции (+ - * / =) - ?
// 2 - звездочка - снаряд для пушки
// 3 - пушка (или снаряд - часть пушки?) (фигура?)
// 4 - ракетка  (фигура?)
// 5 - мячик (фигура?)
// 6 - бомба (срабатывает, если рядом произошло уничтожение кубика)

////____________________________________________________________________________________
 

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

	// Оператор сравнения
	bool operator==(const RGBcolor& other) const
	{ return r == other.r && g == other.g && b == other.b; }
};

// Типы фигур

// Координаты точки
struct Point
{
	int x; // смещение по Х
	int y; // смещение по Y
};

// Расстояния до краев для фигуры (спорно)
struct figSize
{
	int l; // расстояние до края слева
	int r; // расстояние до края справа
	int u; // расстояние до края сверху
	int d; // расстояние до края снизу
};
// Или - матрица самых удаленных кубиков

// Объявление типа указателя на функцию int
//using intFuncPtr = int (*)();
using intFuncPtr = std::function<int()>;

// Объявление типа указателя на функцию RGBcolor
//using colorFuncPtr = RGBcolor (*)();
using colorFuncPtr = std::function<RGBcolor()>;

// Объявление типа указателя на функцию Point
using pointFuncPtr = std::function<Point()>;

//int figTypesCount = 12; // на всякий случай

// Типы фигур (Массивы смещений для каждого кубика)
//std::vector<std::vector<Point>> figTypes;

// Типы фигур (Массивы расстояний до краев фигур)
//std::vector<figSize> figSizes;

//! Что делать с типами кубиков в фигуре?

// Вообще-то расстояния можно считать! Это максимальные и минимальные смещения кубиков в фигуре по осям координат

