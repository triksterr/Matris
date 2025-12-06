#pragma once
// @file: i_render.h

#include "cube.h"
#include <string>

// Интерфейс вывода на экран

class IRender
{
public:
	virtual ~IRender() = default;

	//link:game.h#27
	// Вывод начальной заставки
	//virtual void DrawSplash() = 0;

	// Вывод меню
	//virtual void DrawMenu() = 0;

	// Вывод игры - вывод игрового экрана целиком - на каждый такт перерисовки
	// virtual void DrawGame() = 0;

	// Вывод конца игры

	// Вывод финальной заставки
	
	// Вывод стакана
	virtual void DrawGlass() = 0;

	// Вывод фигуры - ?
	virtual void DrawFigure() = 0;

	// Вывод слоев
	virtual void DrawLayers() = 0;

	// Вывод информации по раунду
	virtual void DrawInfo() = 0;

	// Вывод кубика - private
	virtual void DrawCube(Cube &cube) = 0;

	// Вывод текста - private
	virtual void DrawTxt(std::string text, int x, int y) = 0;

	// Инициализация вывода
	virtual void Init() = 0;

	// Ширина стакана : 10 - 15 кубиков
	// Высота стакана : 15 - 30 кубиков
	// Поля
	// Толщина стакана - 1 квадратик
	// Размер кубика - 3 квадратика

	// Счет		Count
	// Уровень		Level
	// Линий		Lines
	// Фигур		Figs
	// Время		Time
	// Следующая	Next
	// Операций		Ops
	// 9999999999
	// 10 символов

	// Числа на кубиках - не больше 2(3) разрядов
protected:
	// Пишутся при вызове Init()
	int ScreenW; // размер экрана в пикселях 
	int ScreenH;
	int UnitW; // размер минимальной единицы отрисовки (квадратика)
	int UnitH;
	int FontSize; // размер шрифта - в системных единицах
	int FieldW; // размеры полей в единицах отрисовки
	int FieldH;
	int width; // размеры экрана в единицах отрисовки
	int height;
	int cubeW; // размеры кубика в единицах отрисовки
	int cubeH;
};

//! Возможно, не нужна полная перерисовка всего экрана?
// Можно только стирать и записывать динамические элементы

// Альтернатива - перерисовывать все с чатотой 30 кадров
