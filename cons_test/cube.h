#pragma once
// @file: cube.h
#include <cstdint>
#include "types.h"

// Один числовой кубик с цветом
class Cube final
{
private:
	int x; // координата Х (относительно стакана/матрицы)
	int y; // координата Y (относительно стакана/матрицы)
	int sx; // смещение кубика в фигуре по Х относительно центрального кубика (0;0)
	int sy; // смещение кубика в фигуре по Y
	int digit; // число в кубике
	RGBcolor color; // цвет
	int type; // тип кубика: обычный = 0, шарик (*), пушка (=||=), ракетка (===), (вращающийся кубик???)...
	bool visible; // видимость
	bool deleted; // уничтожен - пометка о необходимости удалить

	// Преобразование цветов в RGB в цвет кубика
	RGBcolor rgbToColor(const int r, const int g, const int b)
	{
		color.r = (r > 255 ? 255 : (r < 0 ? 0 : r));
		color.g = (g > 255 ? 255 : (g < 0 ? 0 : g));
		color.b = (b > 255 ? 255 : (b < 0 ? 0 : b));
		return color;
	}

public:
	Cube()
	{
		// Получаем из фигуры координаты

		// Получаем из фигуры цвет
	}
	
	Cube(int x, int y, int number, RGBcolor color, int type = 0)
	{
		this->x = x;
		this->y = y;
		this->digit = number;
		this->color = color;
		visible = true; //! при создании видимость всегда или надо указывать?
		this->type = type;
		sx = 0;
		sy = 0;
		deleted = false;
	}

	Cube(int x, int y, int number, int r, int g, int b, int type = 0) : Cube(x, y, number, rgbToColor(r, g, b)) {}

	Cube(const int x, const int y): Cube(x, y, 0, rgbToColor(127, 127, 127)) {} //! не факт, что этот конструктор нужен
	
	// деструктор
	~Cube() = default;
	//! записать в матрицу nullptr!
	
	// копирующий конструктор
	Cube(const Cube &other)
	{
		x = other.x;
		y = other.y;
		digit = other.digit;
		color = other.color;
		visible = other.visible;
		type = other.type;
		sx = other.sx;
		sy = other.sy;
		deleted = other.deleted;
	}
	
	// Оператор	присваивания
	const Cube &operator=(const Cube &other)
	{
		x = other.x;
		y = other.y;
		digit = other.digit;
		color = other.color;
		visible = other.visible;
		type = other.type;
		sx = other.sx;
		sy = other.sy;
		deleted = other.deleted;
		return *this;
	}

	// сетеры
	void setX(int x) { this->x = x; } // задать координату Х
	void setY(int y) { this->y = y; } // задать координату Y
	void setXY(int x, int y) { this->x = x; this->y = y; } // задать координаты
	void setSX(int sx) { this->sx = sx; } // задать смещение кубика в фигуре по Х
	void setSY(int sy) { this->sy = sy; } // задать смещение кубика в фигуре по Y
	void setSXY(int sx, int sy) { this->sx = sx; this->sy = sy; } // задать смещение кубика в фигуре по Х и Y
	void setRGB(int r, int g, int b) { rgbToColor(r, g, b); } // задать цвет в формате RGB
	void setColor(RGBcolor color) { this->color = color; } // задать цвет
	void setNum(int number) { this->digit = number; } // задать число в кубике
	void setType(int type) { this->type = type; } // задать тип кубика
	void setVisible(bool visible) { this->visible = visible; } // задать видимость кубика

	// геттеры
	int getX() const { return x; }	// получить координату Х
	int getY() const { return y; }	// получить координату Y 
	int getSX() const { return sx; } // получить смещение кубика в фигуре по Х
	int getSY() const { return sy; } // получить смещение кубика в фигуре по Y
	int getNum() const { return digit; } // получить число в кубике
	RGBcolor getRGB() const { return color; }	// получить цвет кубика
	int getR() const { return color.r; }	// получаем компоненты цвета
	int getG() const { return color.g; }
	int getB() const { return color.b; }
	bool getVisible() const	{ return visible; }	// Получить  видимость кубика

	void moveL(int shift = 1) { x -= shift; } // сдвинуть на 1 влево (как быть с проверкой краев?!!!!!!!!!) - а надо ли?
	void moveR(int shift = 1) { x += shift; } // сдвинуть на 1 вправо
	void moveU(int shift = 1) { y += shift; } // сдвинуть на 1 вверх
	void moveD(int shift = 1) { y -= shift; } // сдвинуть на 1 вниз

	void hide() { visible = false; } // скрыть
	void show() { visible = true; } // показать

	void del() { deleted = true; } // пометить для удаления
	bool isDel() const { return deleted; } // помечен на удаление? или живой 

	bool cGlass(); // Проверка касания кубика нижних слоев
	bool cLayers(); // Проверка касания кубика краев стакана
};



