#pragma once
// file: layers.h

#include <vector>
#include "point.h"
#include "cube.h"


//! Координатные оси - стандартно: X - вправо, Y - вверх

// слои - двумерный массив всего стакана - указателей на кубики ( (0, 0) - левый нижний угол)
// хранит указатели на живые кубики упавших фигур
class layers
{
public:
	// Кубики создаются в фигуре, а удаяляются здесь.

	// Удаляем копирование и присваивание
	layers(const layers& other) = delete;
	layers& operator=(const layers& other) = delete;
	// Получение экземпляра синглтона
	static layers& get()
	{
		static layers instance;
		return instance;
	}

	// формируется в начале очередной игры - по размерам стакана
	// Установка размеров - инициализация (по стакану <- из раунда <- из игры)
	void setSizes(int width, int height)
	{ 
		if(width <= 0 || height <= 0)
			; //! ошибка
		//? Возможно - проверка на максимальные размеры?
		
		this->width = width;
		this->height = height;

		cubes.resize(width * height, nullptr); // Ресайз вектора и заполнение nullptr (старое заполнение при изменении размеров не имеет смысла?)
	}
	// Установка размеров через Point
	void setSizes(Point p)
	{
		setSizes(p.x, p.y);
	}
	//! Возможен перенос заполнения слоев из предыдущего раунда или некое случайное заполнение в начале раунда! - зависит от правил раунда

	// Получение кубика по координатарм
	Cube* getCube(int x, int y) const
	{
		if(x >= 0 && x < width && y >= 0 && y < height)
			//return cubes.at(y * width + x); // с проверкой
			return cubes[y * width + x];
		else
			return nullptr; //! ошибка
	}
	// Получение кубика по координатарм через Point
	Cube* getCube(Point p) const
	{
		return getCube(p.x, p.y);
	}
	
	Point getSizes() const
	{
		return { width , height };
	}

	int getWidth() const
	{
		return width;
	}

	int getHeight() const
	{
		return height;
	}

private:
	// Приватный конструктор и деструктор
	layers() = default;
	~layers() = default;

	int width = 1; // ширина - по X
	int height = 1; // высота - по Y
	std::vector<Cube *> cubes; // вектор указателей на кубики
};
