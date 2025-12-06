#pragma once
// @file: c_render.h

#include "i_render.h"
#include "round.h"
#include <windows.h>
#include <consoleapi2.h>
#include <consoleapi3.h>
#include <wincontypes.h>
#include <processenv.h>
#include <string>
#include <cstring>
#include "cube.h"

#include "round.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "info.h"

// Вывод в консоль
class CRender final: public IRender
{
private:
	HANDLE hConsole; // Обработчик консоли
	CONSOLE_CURSOR_INFO originalCursorInfo; // Информация о курсоре
	CONSOLE_SCREEN_BUFFER_INFO originalScreenInfo; // Информация об экране
	CONSOLE_FONT_INFOEX fontInfo; // Информация о шрифте
	
	// Установка позиции курсора
	void setPosition(int x, int y) const
	{
		COORD coord;
		y = height - y - 1;
		coord.X = x > width - 1 ? width - 1 : (x < 0 ? 0 : x);
		coord.Y = y > height - 1 ? height - 1 : (y < 0 ? 0 : y);
		SetConsoleCursorPosition(hConsole, coord);
	}

	// Скрытие курсора
	void hideCursor() const
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(hConsole, &cursorInfo);
		cursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(hConsole, &cursorInfo);
	}

	// Показ курсора
	void showCursor() const
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(hConsole, &cursorInfo);
		cursorInfo.bVisible = TRUE;
		SetConsoleCursorInfo(hConsole, &cursorInfo);
	}

	// Установка размера консоли
	void setSize(const int width, const int height)
	{
		if(width <= 0 || height <= 0)
			return;
		
		// Размер окна консоли
		SMALL_RECT windowSize = {0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1)};
		SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
		// Размер буфера -> совпадает с размером окна: отключение прокрутки
		COORD bufferSize = {static_cast<SHORT>(width), static_cast<SHORT>(height)};
		SetConsoleScreenBufferSize(hConsole, bufferSize);
		this->width = width;
		this->height = height;
	}

	// Очистка экрана
	void clear() const { system("cls"); }

	// Установка цвета текста и фона
	void setColor(int textColor = 7, int backgroundColor = 0) const
	{ SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | textColor); }

	// Установка шрифта
	void setFont(const std::wstring &fontName, const int height = 15, const int width = 5) const
	{
		CONSOLE_FONT_INFOEX fontInfo;
		fontInfo.cbSize = sizeof(fontInfo);
		GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo); // Получаем текущий шрифт

		// Устанавливаем новый шрифт
		wcscpy_s(fontInfo.FaceName, fontName.c_str());
		fontInfo.dwFontSize.X = width;
		fontInfo.dwFontSize.Y = height;
		fontInfo.FontWeight = FW_NORMAL;

		SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
	}

	// Преобразование цвета RGB в цвет консоли
	int rgbToConsoleColor(int r, int g, int b)
	{
		r = std::clamp(r, 0, 255);
		g = std::clamp(g, 0, 255);
		b = std::clamp(b, 0, 255);

		// Рассчитываем яркость
		double brightness = 0.299 * r + 0.587 * g + 0.114 * b;

		// Определяем базовые цвета
		int color = 0;

		// Определяем наличие цветовых компонентов
		bool hasRed = r > 120;
		bool hasGreen = g > 120;
		bool hasBlue = b > 120;

		// Базовый цвет (первые 8 цветов)
		if(hasRed && !hasGreen && !hasBlue) color = 1;    // Красный
		else if(!hasRed && hasGreen && !hasBlue) color = 2; // Зеленый
		else if(hasRed && hasGreen && !hasBlue) color = 3;  // Желтый
		else if(!hasRed && !hasGreen && hasBlue) color = 4; // Синий
		else if(hasRed && !hasGreen && hasBlue) color = 5;  // Пурпурный
		else if(!hasRed && hasGreen && hasBlue) color = 6;  // Голубой
		else if(hasRed && hasGreen && hasBlue) color = 7;   // Белый/серый
		else color = 0; // Черный

		// Если яркость высокая, добавляем 8 для получения светлой версии цвета
		if(brightness > 127 && color != 0 && color != 7)
			color += 8;

		return color;
	}

public:
	// Конструктор
	CRender() // по умолчанию не меняем размеров
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем обработчик консоли

		// Сохраняем оригинальные настройки
		GetConsoleCursorInfo(hConsole, &originalCursorInfo);
		GetConsoleScreenBufferInfo(hConsole, &originalScreenInfo);
		GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

		ScreenW = 0; // размер экрана в пикселях 
		ScreenH = 0;
		UnitW = 0; // размер минимальной единицы отрисовки (квадратика)
		UnitH = 0;
		FontSize = 0; // размер шрифта
		FieldW = 0; // размеры полей
		FieldH = 0;
	}

	// Деструктор
	~CRender() 
	{
		// Восстанавливаем оригинальные настройки
		SetConsoleCursorInfo(hConsole, &originalCursorInfo);
		SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
	}

	//! Инициализация вывода в консоль - может быть перетащить в конструктор?
	void Init() override 
	{
		// Считать размеры окна/экрана - для реального графического экрана
		
		// Ширина: 2 поля экрана + 15 кубиков х3(4) квадратика + 2 толщины стакана + 1 промежуток + 10 символов текста + ?
		// Высота: 2 поля экрана + 30 кубиков х1 квадратик + 1 толщина стакана + ?
		ScreenW = 75; // размер экрана в пикселях 
		ScreenH = 33;
		UnitW = 1; // размер минимальной единицы отрисовки (квадратика)
		UnitH = 1;
		FontSize = 15; // размер шрифта
		FieldW = 1; // размеры полей
		FieldH = 1;
		cubeW = 3; //! размер кубиков - пока 3
		cubeH = 1;

		// Определяем размеры окна в единицах отрисовки
		width = ScreenW / UnitW;
		height = ScreenH / UnitH;
		
		setSize(ScreenW, ScreenH); //! Устанавливаем размеры окна - только для консоли!
		setFont(L"Consolas", FontSize); // Устанавливаем шрифт L"Lucida Console"
		hideCursor(); // Выключаем курсор
	}

	// Вывод стакана
	void DrawGlass() override
	{
		Round &round = Round::getInstance();

		// Начинаем от 0;0 - текущие координаты
		int curX = 0;
		int curY = 0;
		// Смещаемся с учетом полей в начало координат для сткана
		curX += FieldW;
		curY += FieldH;
		// Рисуем левую стенку
		for(int i = 0; i < curY + round.getGlassH() * cubeH; ++i)
			DrawTxt("|", curX, curY + i);
		// Рисуем линию дна
		for(int i = 0; i < round.getGlassW() * cubeW + 2; ++i)
			DrawTxt("-", curX + i, curY);
		// Рисуем правую стенку
		for(int i = 1; i < curY + round.getGlassH() * cubeH; ++i)
			DrawTxt("|", curX + round.getGlassW() * cubeW + 1, curY + i);
	}

	// Вывод фигуры - ?
	void DrawFigure() override
	{}

	// Вывод слоев
	void DrawLayers() override
	{}

	// Вывод информации по раунду
	void DrawInfo() override
	{
		// Читаем текущую информацию по игре
		Info &round = Info::getInstance();

		// get!
		
		// вывод
	}

	// Вывод кубика
	void DrawCube(Cube &cube) override
	{
		if(!cube.getVisible())
			return;
		
		setColor(rgbToConsoleColor(cube.getR(), cube.getG(), cube.getB())); // устанавливаем цвет c преобразованием

		// Пересчет координат матрицы в координаты экрана
		DrawTxt("[" + std::to_string(cube.getNum()) + "]", FieldW + 1 + cube.getX() * cubeW, FieldH + 1 + cube.getY() * cubeH);
	}

	// Вывод текста - в private
	void DrawTxt(std::string text, int x, int y) override
	{
		setPosition(x, y);
		std::cout << text;
	}
};
