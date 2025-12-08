#pragma once
// @file: c_render.h

#include <windows.h>
#include <consoleapi2.h>
#include <consoleapi3.h>
#include <wincontypes.h>
#include <processenv.h>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <climits>
#include <vector>
//#include <tuple>
#include <utility>
#include "i_render.h"
#include "round.h"
#include "cube.h"
#include "types.h"
#include "figure.h"


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
		COORD coord {};
		y = height - y - 1;
		coord.X = x > width - 1 ? width - 1 : (x < 0 ? 0 : x);
		coord.Y = y > height - 1 ? height - 1 : (y < 0 ? 0 : y);
		SetConsoleCursorPosition(hConsole, coord);
	}

	// setPosX(), setPosY() - ?

	// Получение позиции курсора
	void getPosition(int &x, int &y) const
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(hConsole, &info);
		x = info.dwCursorPosition.X;
		y = height - info.dwCursorPosition.Y - 1;
	}

	// Получение X позиции курсора
	int getX() const 
	{ 
		int x, y; 
		getPosition(x, y); 
		return x; 
	}

	// Получение Y позиции курсора
	int getY() const 
	{ 
		int x, y; 
		getPosition(x, y); 
		return y; 
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

	// getSize() - ?

	// Очистка экрана
	void clear() const { system("cls"); }

	// Установка цвета текста и фона
	void setColor(int textColor = 7, int backgroundColor = 0) const
	{ SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | textColor); }

	// Установка цвета текста и фона
	void setColor(RGBcolor colorF, RGBcolor colorB = {0,0,0})
	{ SetConsoleTextAttribute(hConsole, (rgbToConsoleColor(colorB.r, colorB.g, colorB.b) << 4) | rgbToConsoleColor(colorF.r, colorF.g, colorF.b)); }

	// Установка цвета текста
	void setFColor(int textColor = 7) const { SetConsoleTextAttribute(hConsole, textColor); }

	// Установка цвета фона
	void setFColor(RGBcolor color) { setFColor(rgbToConsoleColor(color.r, color.g, color.b)); }

	// Установка цвета фона
	void setBColor(int backgroundColor = 0) const { SetConsoleTextAttribute(hConsole, backgroundColor << 4); }

	// Установка цвета фона
	void setBColor(RGBcolor color) { setBColor(rgbToConsoleColor(color.r, color.g, color.b)); }

	// Получить цвет текста и фона в позиции с координатами x, y
	int GetColor(int x, int y) const
	{
		COORD coord = {x, y};
		WORD attributes = 0;
		DWORD charsRead = 0;

		ReadConsoleOutputAttribute(hConsole, &attributes, 1, coord, &charsRead);
		return attributes;
	}

	// Получить цвет текста и фона из текущей позиции курсора
	int GetColor() const {return GetColor(getX(), getY()); }

	// Получение цвета шрифта
	int getFColor(int x, int y) { return GetColor(x, y) & 0x0F;	}

	// Получение цвета шрифта из текущей позиции курсора
	int getFColor() { return getFColor(getX(), getY()); }

	// Получение цвета фона
	int getBColor(int x, int y) { return (GetColor(x, y) & 0xF0) >> 4; }	//return GetColor(x, y) >> 4;

	// Получение цвета фона из текущей позиции курсора
	int getBColor() { return getBColor(getX(), getY()); }

	// Установка шрифта
	void setFont(const std::wstring &fontName, const int height = 15, const int width = 5) const
	{
		CONSOLE_FONT_INFOEX fontInfo {};
		fontInfo.cbSize = sizeof(fontInfo);
		GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo); // Получаем текущий шрифт

		// Устанавливаем новый шрифт
		wcscpy_s(fontInfo.FaceName, fontName.c_str());
		fontInfo.dwFontSize.X = width;
		fontInfo.dwFontSize.Y = height;
		fontInfo.FontWeight = FW_NORMAL;

		SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
	}

	// Преобразование цвета RGB в цвет консоли (0-15) - более точное
	int rgbToConsoleColor(int r, int g, int b)
	{
		std::swap(r, b); //! какая-то ошибка в порядке цветов!

		// Палитра цветов консоли (R, G, B)
		//static const std::vector<std::tuple<int, int, int>> consoleColors = {
		static const std::vector<RGBcolor> consoleColors = {
			{0, 0, 0},       // 0: черный
			{128, 0, 0},     // 1: красный
			{0, 128, 0},     // 2: зеленый
			{128, 128, 0},   // 3: желтый
			{0, 0, 128},     // 4: синий
			{128, 0, 128},   // 5: пурпурный
			{0, 128, 128},   // 6: голубой
			{192, 192, 192}, // 7: светло-серый
			{128, 128, 128}, // 8: темно-серый
			{255, 0, 0},     // 9: ярко-красный
			{0, 255, 0},     // 10: ярко-зеленый
			{255, 255, 0},   // 11: ярко-желтый
			{0, 0, 255},     // 12: ярко-синий
			{255, 0, 255},   // 13: ярко-пурпурный
			{0, 255, 255},   // 14: ярко-голубой
			{255, 255, 255}  // 15: белый
		};

		int bestColor = 0;
		int minDistance = INT_MAX;

		for(int i = 0; i < 16; i++)
		{
			auto [cr, cg, cb] = consoleColors[i];
			int distance = (r - cr) * (r - cr) + (g - cg) * (g - cg) + (b - cb) * (b - cb);
			if(distance < minDistance)
			{
				minDistance = distance;
				bestColor = i;
			}
		}

		return bestColor;
	}

	// Преобразование цвета RGB в цвет консоли (0-15)
	//int rgbToConsoleColor(int r, int g, int b)
	//{
	//	r = std::clamp(r, 0, 255);
	//	g = std::clamp(g, 0, 255);
	//	b = std::clamp(b, 0, 255);
	//
	//	// Рассчитываем яркость
	//	double brightness = 0.299 * r + 0.587 * g + 0.114 * b;
	//
	//	// Определяем интенсивность каждой компоненты
	//	bool strongRed = r > 128;
	//	bool strongGreen = g > 128;
	//	bool strongBlue = b > 128;
	//
	//	bool weakRed = r > 64;
	//	bool weakGreen = g > 64;
	//	bool weakBlue = b > 64;
	//
	//	// Для серых тонов (все компоненты примерно равны)
	//	int maxVal = std::max({r, g, b});
	//	int minVal = std::min({r, g, b});
	//	bool isGrayish = (maxVal - minVal) < 64;
	//
	//	if(isGrayish)
	//	{
	//		// Серые тона: черный, темно-серый, светло-серый, белый
	//		if(brightness < 32) return 0;          // черный
	//		else if(brightness < 96) return 8;     // темно-серый (яркий черный)
	//		else if(brightness < 224) return 7;    // светло-серый
	//		else return 15;                         // ярко-белый
	//	}
	//
	//	// Определяем базовый цвет
	//	int color = 0;
	//
	//	if(strongRed && !strongGreen && !strongBlue) { color = 1; }			// Красный
	//	else if(!strongRed && strongGreen && !strongBlue) { color = 2; }	// Зеленый
	//	else if(strongRed && strongGreen && !strongBlue) { color = 3; }		// Желтый
	//	else if(!strongRed && !strongGreen && strongBlue) { color = 4; }	// Синий
	//	else if(strongRed && !strongGreen && strongBlue) { color = 5; }		// Пурпурный
	//	else if(!strongRed && strongGreen && strongBlue) { color = 6; }		// Голубой
	//	else // Смешанные цвета - определяем доминирующую компоненту
	//	{
	//		if(r > g && r > b)
	//		{
	//			if(g > b) color = 3;  // ближе к желтому
	//			else color = 5;         // ближе к пурпурному
	//		}
	//		else if(g > r && g > b)
	//		{
	//			if(r > b) color = 3;  // ближе к желтому
	//			else color = 6;         // ближе к голубому
	//		}
	//		else if(b > r && b > g)
	//		{
	//			if(r > g) color = 5;  // ближе к пурпурному
	//			else color = 6;         // ближе к голубому
	//		}
	//		else
	//		{
	//			color = 7;  // белый/серый (но это уже обработано выше)
	//		}
	//	}
	//
	//	// Если яркость высокая и цвет не из серой гаммы, используем яркую версию
	//	if(brightness > 150 && color != 0 && color != 7) { color += 8; }
	//
	//	return color;
	//}

	// Преобразование цвета RGB в цвет консоли (0-15) - более точное
	int rgbToConsoleColor(RGBcolor color) { return rgbToConsoleColor(color.r, color.g, color.b); }

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
		UnitW = 1; // размер минимальной единицы отрисовки (квадратика) в пикселях
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

	// Отрисовка экрана (кадра) целиком


	// Вывод стакана
	void DrawGlass() override
	{
		Round &round = Round::getInstance();

		// цвет стакана - считать из раунда
		RGBcolor color = round.getGlassColor();

		// Начинаем от 0;0 - текущие координаты
		int curX = 0;
		int curY = 0;
		// Смещаемся с учетом полей в начало координат для сткана
		curX += FieldW;
		curY += FieldH;

		// Рисуем левую стенку
		drawLine(curX, curY, curX, curY + round.getGlassH() * cubeH, rgbToConsoleColor(color), '|');
		//for(int i = 0; i < curY + round.getGlassH() * cubeH; ++i)
		//	DrawTxt("|", curX, curY + i);

		// Рисуем правую стенку
		drawLine(curX + round.getGlassW() * cubeW + 1, curY, curX + round.getGlassW() * cubeW + 1, curY + round.getGlassH() * cubeH, rgbToConsoleColor(color), '|');

		// Рисуем линию дна
		drawLine(curX, curY, curX + round.getGlassW() * cubeW + 1, curY, rgbToConsoleColor(color), '-');
		//for(int i = 0; i < round.getGlassW() * cubeW + 2; ++i)
		//	DrawTxt("-", curX + i, curY);

		// Рисуем правую стенку
		//for(int i = 1; i < curY + round.getGlassH() * cubeH; ++i)
		//	DrawTxt("|", curX + round.getGlassW() * cubeW + 1, curY + i);
	}

	// Вывод фигуры - ?
	void DrawFigure(Figure &figure) override
	{
		Round &round = Round::getInstance();

		for(Cube &cube : figure.getCubes())	// пробегаем по вектору кубиков
		{
			DrawCube(cube);
		}
	
		// получаем кординаты, цвета, типы, числа
		// рисуем
	}

	// Вывод слоев
	void DrawLayers() override
	{}

	// Вывод информации по раунду
	void DrawInfo() override
	{
		// Читаем текущую информацию по игре
		Round &round = Round::getInstance();

		// get!
		
		// вывод
	}

	//---- Скорее всего - private:

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

	// Вывод текста - в private
	// @param text - текст для вывода
	// @param x, y - координаты начала вывода
	// @param color - цвет текста
	void DrawTxtC(std::string text, int x, int y, int color)
	{
		setPosition(x, y);
		setFColor(color);
		std::cout << text;
	}

	// Вывод текста - в private
	// @param text - текст для вывода
	// @param x, y - координаты начала вывода
	// @param color - цвет текста
	// @param back - цвет фона
	void DrawTxtC(std::string text, int x, int y, int color, int back)
	{
		setPosition(x, y);
		setColor(color, back);
		std::cout << text;
	}

	//! Разобраться с прототипом и с реализацией дефолта по цвету!

	// Функция для "рисования" линии между двумя точками
	// @param p1, p2 - начало и конец линии
	// @param bl, ur - границы холста
	// @return vector с точками линии в границах холста
	std::vector<Point> calcLine(Point p1, Point p2, Point bl, Point ur)
	{
		std::vector<Point> linePoints;

		int x1 = p1.x;
		int y1 = p1.y;
		int x2 = p2.x;
		int y2 = p2.y;

		// Вычисляем разницы
		int dx = abs(x2 - x1);
		int dy = abs(y2 - y1);

		// Определяем направления
		int sx = (x1 < x2) ? 1 : -1;
		int sy = (y1 < y2) ? 1 : -1;

		int err = dx - dy;

		while(true)
		{
			// Добавляем текущую точку
			linePoints.push_back(Point(x1, y1));

			// Если достигли конечной точки
			if(x1 == x2 && y1 == y2) break;

			int e2 = 2 * err;

			if(e2 > -dy)
			{
				err -= dy;
				x1 += sx;
			}

			if(e2 < dx)
			{
				err += dx;
				y1 += sy;
			}
		}

		// Проверяем координаты на вылет за границы области и обрезаем хвосты

		int x0 = bl.x; // граничные значения
		int y0 = bl.y;
		int xm = ur.x;
		int ym = ur.y;

		// Если в точке одна из координат вылетает за граничные значения - удаляем ее
		linePoints.erase(std::remove_if(linePoints.begin(), linePoints.end(), 
						 [x0, y0, xm, ym](Point p) { return (p.x < x0 || p.y < y0 || p.x > xm || p.y > ym); }), 
						 linePoints.end());

		return linePoints;
	}

	// Рисуем линию
	// координаты - в единицах отрисовки
	// @param size - толщина в единицах отрисовки
	void drawLine(int x1, int y1, int x2, int y2, int color, /*int back,*/ /*int size = 1,*/ char sim = '*')
	{
		Point p1 = {x1, y1}; // точка начала
		Point p2 = {x2, y2}; // точка конца
		Point bl = {0, 0};
		Point ur = {this->width-1, this->height-1};	// получаем размеры
		
		std::vector<Point> line = calcLine(p1, p2, bl, ur); // обсчитываем линию

		std::string s {sim};
		// выводим линию
		for(Point p : line)
		{
			DrawTxtC(s, p.x, p.y, color);
		}
	}
};
