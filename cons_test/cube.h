#pragma once
// @file: cube.h
#include <cstdint>

// Один числовой кубик с цветом
class Cube final
{
private:
	int x; // координата Х (относительно стакана/матрицы)
	int y; // координата Y (относительно стакана/матрицы)
	int sx; // смещение кубика в фигуре по Х относительно центрального кубика (0;0)
	int sy; // смещение кубика в фигуре по Y
	int num; // число в кубике
	uint32_t color; // цвет
	int type; // тип кубика: обычный = 0, шарик (*), пушка (=||=), ракетка (===), (вращающийся кубик???)...
	bool visible; // видимость
	bool deleted; // уничтожен - пометка о необходимости удалить

	// Преобразование цвета RGB в цвет кубика
	uint32_t rgbToColor(const int r, const int g, const int b) { return (r < 0 ? -r : r)*65536 + (g < 0 ? -g : g)*256 + (b < 0 ? -b : b); } // цвет в формате RGB
	//! (r > 255 ? 255 : (r < 0 ? -r : r))

public:
	Cube(int x, int y, int num, uint32_t color, int type = 0)
	{
		this->x = x;
		this->y = y;
		this->num = num;
		this->color = color;
		visible = true; //! при создании видимость всегда или надо указывать?
		this->type = type;
		sx = 0;
		sy = 0;
		deleted = false;
	}

	Cube(int x, int y, int num, int r, int g, int b) : Cube(x, y, num, rgbToColor(r, g, b)) {}

	Cube(const int x, const int y): Cube(x, y, 0, rgbToColor(127, 127, 127)) {} //! не факт, что этот конструктор нужен
	
	// деструктор
	~Cube() = default;
	//! записать в матрицу nullptr!
	
	// копирующий конструктор
	Cube(const Cube &other)
	{
		x = other.x;
		y = other.y;
		num = other.num;
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
		num = other.num;
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
	void setRGB(int r, int g, int b) { this->color = rgbToColor(r, g, b); } // задать цвет в формате RGB
	void setColor(uint32_t color) { this->color = color; } // задать цвет
	void setNum(int num) { this->num = num; } // задать число в кубике
	void setType(int type) { this->type = type; } // задать тип кубика
	void setVisible(bool visible) { this->visible = visible; } // задать видимость кубика

	// геттеры
	int getX() const { return x; }	// получить координату Х
	int getY() const { return y; }	// получить координату Y 
	int getSX() const { return sx; } // получить смещение кубика в фигуре по Х
	int getSY() const { return sy; } // получить смещение кубика в фигуре по Y
	int getNum() const { return num; } // получить число в кубике
	uint32_t getRGB() const { return color; }	// получить цвет кубика - ?
	int getR() const { return color & 0xFF; }	// получаем компоненты цвета
	int getG() const { return (color >> 8) & 0xFF; }
	int getB() const { return color >> 16; }
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



