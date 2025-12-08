#pragma once
// @file: rules.h

#include "round.h"
#include "types.h"
#include "rules.h"
#include <random>
#include <chrono>


// Функции-генераторы

// Инициализация генератора случайных чисел
std::mt19937 &initRnd()
{
	// текущее время в милисекундах
	auto now = std::chrono::system_clock::now().time_since_epoch();
	auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();

	// вихрь Мерсенна
	static std::mt19937 gen(now_ms);

	//static std::mt19937 gen(std::random_device {}());

	return gen;
}

// Получение случайного значения
// @param left, right - границы диапазона выдаваемых значений
int getRnd(int left, int right)
{
	// равномерное распределение с диапазоном
	std::uniform_int_distribution<int> dist(left, right);

	return dist(initRnd());
}

// Правила 

// 1. Простейший раунд
// Фон - черный
// Стакан - белый
// Размеры стакана 10 на 15
//! Текст справа: количество очков, количество упавших кубиков, время
// Цвет текста - серый
// Сверху произвольно появляется одиночный кубик (fig[0])
// случайного светлого цвета != черному
// с однозначным числом 0 - 9
// Начинает падать с минимальной скоростью
// Его можно сдвигать влево-вправо, вниз и сбросить
// Если кубик, на который он упал (по вертикали), дает с ним в сумме 10, оба кубика уничтожаются
// Время неограничено - ?
// Количество неограничено - ?
// Игру можно поставить на паузу или прекратить
// В конце - результаты

//! Указатели на Генераторы - в раунде, а здесь - они сами и условия их инициализации и выдачи
 
// Генератор целого
int GenInt(int left, int right) { return getRnd(left, right); }

//! Генератор цвета - в диапазонах!
RGBcolor GenColor() { return {getRnd(0, 255), getRnd(0, 255), getRnd(0, 255)}; }

// Генератор точки - в пределах стакана
Point GenPoint() { return {getRnd(0, Round::getInstance().getGlassW() - 1), getRnd(0, Round::getInstance().getGlassH() - 1)}; }

// Генератор точки - в заданных пределах
Point GetPoint(int left, int bottom, int right, int top) { return {getRnd(left, right), getRnd(bottom, top)}; }

//? --- Генераторы позиции появления фигуры

// Генератор позиции появления фигуры - сверху в центре
Point GenFigPos0()
{
	Point p;
	Round &round = Round::getInstance(); // получаем раунд
	p.x = (round.getGlassW() - 1) / 2;
	p.y = round.getGlassH() - 1;
	return p;
}

// Генератор позиции появления фигуры - сверху, cлучайная по х
Point GenFigPos1()
{
	Point p;
	p.x = getRnd(0, Round::getInstance().getGlassW() - 1);
	p.y = Round::getInstance().getGlassH() - 1;
	return p;
}

//? --- Генераторы типов фигур

// Генератор типа фигуры - 0. Одиночный кубик
int GenFigType0() { return 0; }

// Генератор типа фигуры (0 - 1) Одиночный кубик, Палка из 2 кубиков
int GenFigType1() { return getRnd(0, 1); }

// Генератор типа фигуры (0 - 2) Одиночный кубик, Палка из 2 кубиков, Палка из 3 кубиков
int GenFigType2() { return getRnd(0, 2); }

//? --- Генераторы цвета фигур

// Генератор цвета фигуры - белый
RGBcolor GenFigColor0() { return {255, 255, 255}; }

// Генератор цвета фигуры - случайный светлый
RGBcolor GenFigColor1() { return {getRnd(100, 255), getRnd(100, 255), getRnd(100, 255)}; }

//? --- Генераторы углов поворота фигуры

// Генератор угла поворота фигуры - не поворачивать
int GenAngle0() { return 0; }

// Генератор угла поворота фигуры - 0, 90, 180, 270
int GenAngle1() { return getRnd(0, 3) * 90; }

//? --- Генераторы типов кубиков

// Генератор типа кубика - обычный числовой кубик
int GenCubeType0() { return 0; }

//? --- Генераторы цвета кубика

// Генератор цвета кубика - белый
RGBcolor GenCubeColor0() { return {255, 255, 255}; }

// Генератор цвета кубика - случайный светлый
RGBcolor GenCubeColor1() { return {getRnd(100, 255), getRnd(100, 255), getRnd(100, 255)}; }

//? --- Генераторы чисел в кубике

// Генератор числа в кубике (0-9)
int GenCubeNum0() { return getRnd(1, 9); }

// Функция вычисления правила уничтожения

//! После того, как фигура уперлась (не может больше падать) она переходит в слои, затем запускается функция проверки всех кубиков в слоях на предмет выполнения правил уничтожения. Если правило уничтожения сработало, а в слоях еще есть кубики, функция проверки запускается снова. И так до тех пор, пока после полного прохода правило уничтожения не сработало.

// Правила - это функции с ГСЧ или без, на наборах или диапазонах значений

// Вычисления могут быть горизонтально, вертикально, по диагоналям

// При задании типа фигуры может быть задана матрица типов кубиков



// Поворот точки на фикс. углы (по 90) относительно начала координат
Point rotate(Point point, int angle)
{
	while(angle > 270) //! убираем лишние обороты
		angle -= 360;

	if(angle == 90) // 90: (x, y) -> (-y, x)
	{
		std::swap(point.x, point.y);
		point.x = -point.x;
	}

	if(angle == 180) // 180: (x, y) -> (-x, -y)
	{
		point.x = -point.x;
		point.y = -point.y;
	}

	if(angle == 270) // 270: (x, y) -> (y, -x)
	{
		std::swap(point.x, point.y);
		point.y = -point.y;
	}

	return point;
}
