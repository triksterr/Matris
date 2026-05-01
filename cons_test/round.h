#pragma once
// @file: round.h
//
#include "types.h"
#include "rules.h"
#include <vector>
#include <string>


// Раунд игры - все правила и данные текущего раунда

class Round final
{
public:
	// Удаляем копирование и присваивание
	Round(const Round &) = delete;
	Round &operator=(const Round &) = delete;

	// Получение экземпляра синглтона
	static Round &getInstance()
	{
		static Round instance;
		return instance;
	}
	
	//void Init(); //! ??????? может и не надо
	// Инициализируем матрицу ?

	// Следующий раунд
	//void Next();
		 
	// сеттеры
	void setGlass(int width, int height) { glassW = width; glassH = height; } // размеры стакана
	void setGlassColor(RGBcolor color) { glassColor = color; } // цвет стакана
	void setGlassColor(int r, int g, int b) { glassColor.r = r; glassColor.g = g; glassColor.b = b; } // цвет стакана
	void setCube(int width, int height) { cubeW = width; cubeH = height; } // размеры кубика

	// геттеры
	int getGlassW() const { return glassW; } // получение размеров стакана в кубиках
	int getGlassH() const { return glassH; }
	int getCubeW() const { return cubeW; } // получение размеров кубика в единицах отрисовки
	int getCubeH() const { return cubeH; }
	RGBcolor getGlassColor() const { return glassColor; }

	intFuncPtr getGenFig() const { return figGen; } // получить генератор фигур
	colorFuncPtr getGenFigColor() const { return figColorGen; } // получить генератор цвета фигур
	pointFuncPtr getGenFigPos() const { return figPosGen; } // получить генератор начальной позиции фигур
	intFuncPtr getGenAngle() const { return figAngleGen; } // получить генератор угла
	intFuncPtr getCubeNum() const { return cubeNumGen; }

	////_________________________________________________________________________________________

	// Info
	// сеттеры
	void nextLevel() { level++; }
	void setLevel(int level) { this->level = level; }

	void addScore() { levelScore++; totalScore++; } //! на сколько увеличивать счет?

	// геттеры


	//! Можно добавить методы для сброса состояния при перезапуске раунда - ???
	void reset() //! по идее, надо сбрасывать все в 0 и затем записывать нужные значения
	{
		glassW = 5;
		glassH = 20;
		cubeW = 3;
		cubeH = 1;

		glassColor = { 127, 127, 127 };
		level = 1;
		levelScore = 0;
		totalScore = 0;

		figGen = GenFigType4; // любая фигура
		figColorGen = GenFigColor1;
		figPosGen = GenFigPos1;
		figAngleGen = GenAngle1;
		//figAngleGen = GenAngle0; // не поворачивать
		cubeNumGen = GenCubeNum0;
	}
	
private:
	// Приватный конструктор и деструктор
	Round() = default;
	~Round() = default;

	int glassW = 5,
		glassH = 20; // размеры стакана/матрицы кубиков в кубиках
	int cubeW = 3, 
		cubeH = 1; // размеры кубика в единицах отрисовки (лучше - в квадратиках)
	RGBcolor glassColor = { 127, 127, 127 }; // цвет стакана

	// Цвета текста
	// Фона
	// Стакана
	//

	// Слева отступ - толщина стенки стакана в единицах отрисовки = 1
	// Снизу отступ - толщина дна стакана в единицах отрисовки = 1
	// Поля по экрану - отступы в единицах отрисовки (сейчас = 0)
	
	// временной такт - скорость падения
	// правила самого раунда:
	intFuncPtr figGen; // - типы фигур - ссылка на функцию-генератор
	colorFuncPtr figColorGen; // - цвета фигур - ссылка на функцию-генератор
	intFuncPtr figAngleGen; // - углы поворота фигур - ссылка на функцию-генератор
	pointFuncPtr figPosGen; // - места появления фигур - ссылка на функцию-генератор
	// - типы кубиков - либо по типу фигуры, либо по правиам самого раунда
	// - цвета кубиков - по правиам раунда - ссылка на функцию-генератор
	intFuncPtr cubeNumGen; // - правило генерации чисел в фигуре - ссылка на функцию
	// - правило расстановки чисел (знаков) в фигуре: разрядность чисел и диапазон, размещение
	// - правило уничтожения кубиков - ссылка на функцию	
	// - правило перехода в слои (возможно, изменение типа кубиков, значений или их цвета) - ссылка на функцию
	// - бонусы
	// - количество фигур в течение всего раунда
	// - правило завершения раунда: количество уничтоженных кубиков, количество упавших кубиков, ограничения по времени, количество решенных примеров (возможно, с учетом количества ошибок) - ссылка на функцию



	// Текущее состояние Info (static):
	int level = 1;	// Текущий ровень (порядковый номер раунда)
	int levelScore; // Счет раунда - очки
	int totalScore; // Счет всей игры
	int levelCubes = 0;	// Количество уничтоженных кубиков в этом раунде
	int totalCubes = 0;	// Количество уничтоженных кубиков во всей игре
	// Количество упавших кубиков - ?
	int levelFigs = 0;	// Количество упавших фигур в этом раунде
	int totalFigs = 0;	// Количество упавших фигур во всей игре
	int levelTime = 0;	//! Время уровня(раунда) - Не int !
	int totalTime = 0; //! Время всей игры - Не int !
	int levelOps = 0; // Количество успешных операций (примеров) за раунд
	int totalOps = 0; // Количество успешных операций (примеров) всего
	int levelErrs = 0;	// Количество ошибок за раунд
	int totalErrs = 0;	// Количество ошибок всего
		//! - текущая и следующая фигуры - Не int !

	// сделать как в Digger: раунд может закончиться если упали все фигуры данного раунда или если что-то выполнили
	// призовые фишки: уничтожение слоев, кубиков с  пушка, ракетка с шариком, .....

		// Текстовые константы
	std::vector<std::string> txt_ru = {
		"Счет:",		// 0
		"Уровень:",		// 1
		"Линий:",		// 2
		"Фигур:",		// 3
		"Время:",		// 4
		"Следующая:",	// 5
		"Операций:",	// 6
	};

	std::vector<std::string> txt_en = {
		"Count:",		// 0
		"Level:",		// 1
		"Lines:",		// 2
		"Figs:",		// 3
		"Time:",		// 4
		"Next:",		// 5
		"Ops:",			// 6
	};
};

// такт раунда - такт перерисовки, потому что больше на экране ничего принципиально не изменяется.
// или можно задать кадровую частоту и определять так раунда в кадрах - 30 к/сек ?
