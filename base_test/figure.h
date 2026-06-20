#pragma once
// file: figure.h

#include <cassert>
#include <vector>
#include "types.h"
#include "point.h"
#include "rgbcolor.h"
#include "cube.h"
#include "round.h"


//! Координатные оси - стандартно: X - вправо, Y - вверх

	// Кубики создаются здесь, а удаяляются - в слоях.

	// в конструкторе - создаем фигуру из кубиков по правилам раунда (пока без привязки к стакану)
	// поворачиваем по правилам раунда (пока без привязки к стакану)
	// по правилам раунда получаем точку привязки угла
	// проверяем на попадание в стакан и сдвигаем точку привязки угла с учетом размеров фигуры - чтобы точно попадать в стакан

	//! TODO Получать цвет кубика из фигуры - в конструкторе кубика, вызываемом из фигуры - с учетом правил раунда
	 
	//! Из раунда - начальные координаты фигуры.	
	//! Координаты кубика генерирует и хранит фигура!


//! КОД СГЕНЕРИРОВАН ИИ - ВЕСЬ ПРОВЕРИТЬ!!!


// фигура
class Figure
{
public:
	// Конструктор
	Figure()
	{
		Round& round = Round::get(); // получаем раунд

		// получаем из раунда вид фигуры (матрица смещений и центр)
		// получаем из раунда точку привязки (координаты) фигуры

		// получаем из раунда цвет фигуры / правило генерации цветов кубиков
		// получаем из раунда правило генерации типов кубиков
		// получаем из раунда правило генерации чисел кубиков

		// создаем кубики
	}


	////______________________________________________________________________________________________
	// Конструктор
	// Создает фигуру выбранного типа, заполняет матрицу смещений и создает кубики.
	// base - глобальная точка привязки фигуры в стакане.
	// startDigit - стартовое число для заполнения кубиков (дальше +1 по индексу).
	Figure( int figType = 0,
		Point base = { 0, 0 },
		RGBcolor color = { 255, 255, 255 },
		int startDigit = 1)
		: base(base), color(color)
	{
		setFromType(figType, startDigit);
	}

	// До передачи в layers фигура владеет своими кубиками и удаляет их сама.
	~Figure()
	{
		clearOwnedCubes();
	}

	// Копирование запрещено: фигура владеет сырыми указателями на кубики.
	Figure(const Figure& other) = delete;
	Figure& operator=(const Figure& other) = delete;

	// Move-конструктор: переносит владение кубиками и метаданные фигуры.
	// Объект-источник очищаем до нейтрального состояния.
	Figure(Figure&& other) noexcept
		: cubes(std::move(other.cubes)),
		cpos(std::move(other.cpos)),
		base(other.base),
		center(other.center),
		color(other.color)
	{
		other.cubes.clear();
		other.cpos.clear();
		other.base = { 0, 0 };
		other.center = { 0, 0 };
	}

	// Move-присваивание: сначала освобождаем текущие кубики,
	// затем забираем владение у объекта-источника.
	Figure& operator=(Figure&& other) noexcept
	{
		if (this == &other)
			return *this;

		clearOwnedCubes();

		cubes = std::move(other.cubes);
		cpos = std::move(other.cpos);
		base = other.base;
		center = other.center;
		color = other.color;

		other.cubes.clear();
		other.cpos.clear();
		other.base = { 0, 0 };
		other.center = { 0, 0 };
		return *this;
	}

	// Переинициализация фигуры по типу:
	// 1) проверка индексов типа/центра,
	// 2) удаление старых кубиков,
	// 3) копирование смещений и центра,
	// 4) создание нового набора кубиков.
	bool setFromType(int figType, int startDigit = 1)
	{
		if (figType < 0 || figType >= static_cast<int>(figTypes.size()))
			return false;
		if (figType >= static_cast<int>(figCenters.size()))
			return false;

		clearOwnedCubes();

		cpos = figTypes[figType];
		center = figCenters[figType];

		cubes.reserve(cpos.size());
		for (size_t i = 0; i < cpos.size(); ++i)
		{
			Cube* c = new Cube(startDigit + static_cast<int>(i), color, 0);
			cubes.push_back(c);
		}
		assert(cubes.size() == cpos.size());
		return true;
	}

	// Изменить глобальную точку привязки фигуры в стакане (положение фмгуры).
	void setBase(Point p)
	{
		base = p;
	}

	Point getBase() const
	{
		return base;
	}

	Point getCenter() const
	{
		return center;
	}

	RGBcolor getColor() const
	{
		return color;
	}

	// Количество кубиков в фигуре.
	size_t getCubeCount() const
	{
		return cubes.size();
	}

	const std::vector<Point>& getLocalOffsets() const
	{
		return cpos;
	}

	// Возвращает глобальные координаты кубиков:
	// global = base + localOffset.
	std::vector<Point> getGlobalPositions() const
	{
		std::vector<Point> result;
		result.reserve(cpos.size());
		for (const Point& p : cpos)
			result.push_back({ base.x + p.x, base.y + p.y });
		return result;
	}

	//TODO - TEST Константный метод доступа к кубикам фигуры
	const std::vector<Cube*>& getCubes() const
	{
		return cubes;
	}

	//TODO - TEST Возвращает кубики (итератор) - TEST
	std::vector<Cube*>::const_iterator begin() const
	{
		return cubes.begin();
	}
	std::vector<Cube*>::const_iterator end() const
	{
		return cubes.end();
	}

	// Передача владения слоям
	// после вызова figure больше не владеет кубиками и не пытается их удалить в деструкторе.
	std::vector<Cube*> releaseCubes()
	{
		std::vector<Cube*> released = std::move(cubes);
		cubes.clear();
		return released;
	}

private:
	// Внутренняя очистка всех кубиков, которыми владеет figure.
	void clearOwnedCubes()
	{
		for (Cube* c : cubes)
			delete c;
		cubes.clear();
	}

	std::vector<Cube *> cubes; // указатели на кубики
	std::vector<Point> cpos; // матрица смещений относительно угла привязки (с учетом поворота)
	// размеры векторов - одинаковые, индекс кубика = индексу смещения
	// поворачиваем только матрицу смещений (меняем локальные координаты для каждого кубика)
	// сдвигаем всю фигуру - меняем глобальные координаты угла привязки
	Point base; // координаты угла привязки (~левый верхний в фигуре) - в стакане
	Point center; // координаты центра поворота относительно угла привязки в кубике (*2 для целых кубиков) если нечетные - значит между 2 или 4 кубиками
	RGBcolor color; // цвет всей фигуры
	
	//int type; // тип фигуры: по списку типов (палка, квадрат, уголок....) - или что-то другое?
	// расстояния до краев - считаются из матрицы
	//int num = 0; // количество кубиков в фигуре - в принципе не нужно, но легко получается из размера
	//int angle; // угол поворота фигуры относительно базового положения (0, 90, 180, 270 )
	// угол - для информации! Все координаты пересчитываем по результатам поворота!
	//bool visible; // видимость
	//bool deleted; // уничтожена - пометка о необходимости удалить
};
