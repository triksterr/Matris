#pragma once
// @file: layers.h
//

#include <vector>
#include "cube.h"
#include "round.h"
#include "game.h"


// Матрица нижних слоев в стакане
//! Фактически - это еще одна фигура, только с другоми законами
class Layers
{
public:
// Удаляем копирование и присваивание
	Layers(const Layers &other) = delete;
	Layers &operator=(const Layers &other) = delete;

	// Получение экземпляра синглтона
	static Layers &getInstance()
	{
		static Layers instance;
		return instance;
	}

	// Инициализация матрицы слоев - по раунду
	void Init()
	{
		data.clear(); // сброс вектора

		Round &round = Round::getInstance(); // получаем раунд
		data.resize(round.getGlassW() * round.getGlassH(), nullptr); // задание размера и очистка вектора

		// Начальное заполнение слоев по правилу раунда
		// Получаем из раунда функцию-генератор начального заполнения слоев и выполняем ее
	}

	//! Возможен перенос заполнения слоев из предыдущего раунда! - зависит от правила раунда

	//! Из раунда - координаты фигуры.	
	//! Координаты кубика генерирует фигура!


	// Записать кубик в матрицу
	// @param cube - указатель на кубик
	// @return true - если запись прошла успешно (место не было занято и в границах стакана)
	bool writeCube(Cube *cube)
	{
		if(cube == nullptr)
			return false;

		if(outOfGlass(cube->getX(), cube->getY())) // если вылет за стакан
			return false;
		if(isCube(cube->getX(), cube->getY())) // если позиция занята
			return false;

		data.at(Round::getInstance().getGlassW() * cube->getY() + cube->getX()) = cube;
		return true;
	}

	// Считать кубик из позиции
	// @param x - координата по x
	// @param y - координата по y
	// @return указатель на кубик (nullptr - если позиция пуста или вылет за стакан)
	Cube *readCube(int x, int y) const 
	{ 
		if(outOfGlass(x, y))  // если вылет за стакан
			return nullptr;

		return data.at(Round::getInstance().getGlassW() * y + x); 
	}
	
	// Удалить кубик из матрицы слоев по координатам
	// @param x - координата по x
	// @param y - координата по y
	// @return true - если удаление прошло успешно (место было не пустое и в границах стакана)
	bool delCube(int x, int y)
	{
		if(outOfGlass(x, y)) // если вылет за стакан
			return false;

		if(isCube(x, y)) // если позиция занята
		{
			data.at(Round::getInstance().getGlassW() * y + x) = nullptr;
			return true;
		}
		else
			return false;
	}

	// Удалить заданный кубик из матрицы слоев
	// @param cube - указатель на кубик
	// @return true - если удаление прошло успешно
	bool delCube(Cube *cube)
	{
		if(cube == nullptr)
			return false;

		return delCube(cube->getX(), cube->getY());
	}

	//! В какой момент помечаем кубик на удаление????!!!!!
	
	// Проверить наличие в слоях кубика
	// @param x - координата по x
	// @param y - координата по y
	// @return true - если кубик есть
	bool isCube(int x, int y) const
	{ 
		if(outOfGlass(x, y))  // если вылет за стакан
			return false;
		else
			return (data.at(Round::getInstance().getGlassW() * y + x) != nullptr); 
	}

	// Проверить наличие в слоях кубика по его указателю
	// @param cube - указатель на кубик
	// @return true - если этот кубик есть в слоях
	bool isCube(Cube *cube) const
	{
		if(cube == nullptr)
			return false;

		return isCube(cube->getX(), cube->getY());
	}

	// Проверить наличие кубика по смещению от данного кубика
	// @param cube - указатель на кубик
	// @param sx - смещение по x
	// @param sy - смещение по y
	// @return true - если по смещению от данного кубика есть кубик
	bool isNear(Cube *cube, int sx, int sy) const
	{
		if(cube == nullptr)
			return false;

		return isCube(cube->getX() + sx, cube->getY() + sy);
	}

	bool isNear(int x, int y, int sx, int sy) const { return isCube(x + sx, y + sy); }

	// Проверить наличие кубика снизу
	// @param x - координата по x
	// @param y - координата по y
	// @return true - если снизу есть кубик
	bool isBelow(int x, int y) const { return (isCube(x, y - 1)); }

	bool isBelow(const Cube *cube) const
	{
		if(cube == nullptr)
			return false;

		return isBelow(cube->getX(), cube->getY());
	}

	// Проверить наличие соседних кубиков по осям (по крестику)
	// @param x - координата по x
	// @param y - координата по y
	// @return true - если соседи есть
	bool isNearXY(int x, int y) const { return (isCube(x + 1, y) || isCube(x - 1, y) || isCube(x, y + 1) || isCube(x, y - 1)); }

	bool isNearXY(Cube *cube) const
	{
		if(cube == nullptr)
			return false;

		return isNearXY(cube->getX(), cube->getY());
	}

	// Проверить наличие соседних кубиков по диагоналям (по диагональному крестику)
	// @param x - координата по x
	// @param y - координата по y
	// @return true - если соседи есть
	bool isNearDiag(int x, int y) const { return (isCube(x + 1, y + 1) || isCube(x - 1, y - 1) || isCube(x - 1, y + 1) || isCube(x + 1, y - 1)); }

	bool isNearDiag(Cube *cube) const
	{
		if(cube == nullptr)
			return false;

		return isNearDiag(cube->getX(), cube->getY());
	}

	// Проверить наличие любых соседних кубиков
	// @param x - координата по x
	// @param y - координата по y
	// @return true - если соседи есть
	bool isNears(int x, int y) const { return (isNearXY(x, y) || isNearDiag(x, y)); }

	bool isNears(Cube *cube) const
	{
		if(cube == nullptr)
			return false;

		return isNears(cube->getX(), cube->getY());
	}

	// Определить самый верхний кубик в столбце
	// @param x - координата по x
	// @return координата y самого верхнего кубика в столбце
	int getYmax(int x) const
	{
		Round& round = Round::getInstance(); // получаем раунд

		for(int i = round.getGlassH() - 1; i >= 0; i--)
			if(readCube(x, i) != nullptr)
				return i;
		
		return -1; // столбец пуст
	}

	// Цикл прохода по всем кубикам слоёв с заданной функцией
	//template<typename Func> // с шаблоном
	//bool eachCube(Func&& fun)
	bool eachCube(bool (*fun)(Cube))
	{
		for(auto &cube : data)
		{
			if(cube == nullptr)
				continue;
			if(!fun(*cube))
				return false;
		}
		return true;
	}

private:
// Приватный конструктор и деструктор
	Layers() = default;
	~Layers() = default;

	// Проверка вылета координат за стакан
	bool outOfGlass(int x, int y) const
	{
		Round &round = Round::getInstance(); // получаем раунд

		return (x < 0 || x > round.getGlassW() - 1 || y < 0 || y > round.getGlassH() - 1);
	}

	std::vector<Cube *> data; // вектор указателей на кубики
};
