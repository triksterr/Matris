#pragma once
// file: c_render.h

// Buffered WinAPI console renderer.

#include <windows.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#include "..\interface\i_render.h"
#include "..\types.h"
#include "..\cube.h"
#include "..\figure.h"

////________________________________________________________________________________________

// Рисовать все объекты мы можем, используя стандартные шрифты (3-4 размера),
// БК и пиксели.
// поэтому все можно перенести в iRender, оставить здесь только реализацию этих примиивов для данного варианта/OS


// цикл отрисовки в раунде по тактам
//while(running)
//{
//  // 0. Начало тайминга
//  const int targetFPS = 30; // 30 кадров в секунду
//  const auto frameDuration = std::chrono::milliseconds(1000 / targetFPS);
//  auto lastFrame = std::chrono::steady_clock::now();
// 
//	// 1. обновляем состояние игры - выполняем всю внутриигровую логику (повороты, сдвиги, сбросы, и т.д.)
//
//		Пишем кадр
//	// 2. начинаем новый кадр - renderer.beginFrame(); - очищаем backbuffer (готовим под новый кадр)
//	// 3. draw scene - пишем все новое в буфер - drawFrame(), куда входит:
//	renderer.drawGlass(...);
//	renderer.drawFigure(currentFigure);
//	renderer.drawLayers();
//	renderer.drawInfo();
//  renderer.drawButtons();
//
//		Выводим кадр
//	// 4. отрисовка кадра - renderer.updateFrame(); - вывели в консоль
//
//	// 5. тактовая пауза (конец тайминга)
//  auto now = std::chrono::steady_clock::now();
//  auto elapsed = now - lastFrame;
//  if(elapsed < frameDuration)
//	  std::this_thread::sleep_for(frameDuration - elapsed);
//  lastFrame = std::chrono::steady_clock::now();
//}

////________________________________________________________________________________________

// TODO: перенести в iRender независимые реализации!

// TODO: реализовать обсчет параметров экрана

// вывод в консоль Windows
class cRender final : public iRender
{
private:
	HANDLE hConsole = INVALID_HANDLE_VALUE; // Консоль

	CONSOLE_CURSOR_INFO originalCursorInfo {};
	CONSOLE_SCREEN_BUFFER_INFO originalScreenInfo {};
	CONSOLE_FONT_INFOEX originalFontInfo {};

	// Задаем параметры вручную (правильно - надо бы получать и обсчитывать!)
	//
	//int width = 0;
	//int height = 0;
	//
	//int ScreenW = 75;
	//int ScreenH = 33;
	//
	//int UnitW = 1;
	//int UnitH = 1;
	//
	//int FontSize = 16;
	//
	//int FieldW = 1;
	//int FieldH = 1;
	//
	//int cubeW = 3;
	//int cubeH = 1;
	//
	//! Перенесли в конструктор link:C:\Users\Alex\Documents\prog\matris\base_test\win_cons\c_render.h://%20конструктор%20(инициализация%20консоли)
	
	std::vector<CHAR_INFO> backBuffer; // основной framebuffer консоли, в который пишется новый кадр (каждый элемент содержит: символ + цвет)
	// Одна ячейка = один символ + два цвета
	//struct Cell
	//{
	//	char ch; // символ 2B
	//	uint8_t fg; // цвет текста 1B
	//	uint8_t bg; // цвет фона 1B
	//};
	std::vector<CHAR_INFO> frontBuffer; // второй framebuffer - для кадра, который показывается сейчас

	// Палитра консоли (приведение RGB)
	static constexpr std::array<RGBcolor, 16> consoleColors =
	{
		RGBcolor{0, 0, 0},         // 0
		RGBcolor{128, 0, 0},       // 1
		RGBcolor{0, 128, 0},       // 2
		RGBcolor{128, 128, 0},     // 3
		RGBcolor{0, 0, 128},       // 4
		RGBcolor{128, 0, 128},     // 5
		RGBcolor{0, 128, 128},     // 6
		RGBcolor{192, 192, 192},   // 7
		RGBcolor{128, 128, 128},   // 8
		RGBcolor{255, 0, 0},       // 9
		RGBcolor{0, 255, 0},       // 10
		RGBcolor{255, 255, 0},     // 11
		RGBcolor{0, 0, 255},       // 12
		RGBcolor{255, 0, 255},     // 13
		RGBcolor{0, 255, 255},     // 14
		RGBcolor{255, 255, 255}    // 15
	};

private:
	// Преобразование координат renderer -> console.
	// Renderer: (0,0) bottom-left -> Console: (0,0) top-left
	inline int toConsoleY(int y) const noexcept
	{
		return field.height - y - 1;
	}

	// Преобразование координат renderer -> console.
	// Renderer: (0,0) bottom-left -> Console: (0,0) top-left
	Point toConsoleX(int x) const noexcept
	{
		return x;
	}

	// Проверка на выход за границы окна
	inline bool inBounds(int x, int y) const noexcept
	{
		return x >= 0 && y >= 0 && x < field.width && y < field.height;
	}

	// Преобразование координат renderer -> в смещение в backbuffer
	inline int bufferIndex(int x, int y) const noexcept
	{
		if(!inBounds(x, y))
			return -1; //! ошибка!

		return toConsoleY(y) * field.width + x;
	}

	// WinAPI обертки

	// Проверка ошибок WinAPI
	void checkWinAPI(BOOL result, const char* msg) const
	{
		if(result)
			return;

		DWORD err = GetLastError();

		// В production:
		//   logger
		//   debugger output
		//   exception
		// Пока assert.

		//assert(result && msg);
		assert(false && "WinAPI call failed"); //! - сюда ERR
		(void)err; // просто блокируем предупреждение C4101
		(void)msg;
	}

	// Скрытие курсора
	void hideCursor() const
	{
		CONSOLE_CURSOR_INFO ci {};

		checkWinAPI(GetConsoleCursorInfo(hConsole, &ci), "GetConsoleCursorInfo");

		ci.bVisible = FALSE;

		checkWinAPI(SetConsoleCursorInfo(hConsole, &ci), "SetConsoleCursorInfo");
	}

	// Показ курсора
	void showCursor() const
	{
		CONSOLE_CURSOR_INFO ci {};

		checkWinAPI(GetConsoleCursorInfo(hConsole, &ci), "GetConsoleCursorInfo");

		ci.bVisible = TRUE;

		checkWinAPI(SetConsoleCursorInfo(hConsole, &ci), "SetConsoleCursorInfo");
	}

	// Установка шрифта
	void setFont(const std::wstring& fontName, int fontHeight, int fontWidth = 0) const
	{
		CONSOLE_FONT_INFOEX cfi {};
		cfi.cbSize = sizeof(cfi);

		checkWinAPI(GetCurrentConsoleFontEx(hConsole, FALSE, &cfi), "GetCurrentConsoleFontEx");

		wcscpy_s(cfi.FaceName, fontName.c_str());

		cfi.dwFontSize.X = static_cast<SHORT>(fontWidth);
		cfi.dwFontSize.Y = static_cast<SHORT>(fontHeight);

		checkWinAPI(SetCurrentConsoleFontEx(hConsole, FALSE, &cfi), "SetCurrentConsoleFontEx");
	}

	// Resize консоли
	void setSize(int newWidth, int newHeight)
	{
		assert(newWidth > 0);
		assert(newHeight > 0);

		field.width = newWidth;
		field.height = newHeight;

		COORD bufferSize
		{
			static_cast<SHORT>(newWidth),
			static_cast<SHORT>(newHeight)
		};

		SMALL_RECT windowRect
		{
			0,
			0,
			static_cast<SHORT>(newWidth - 1),
			static_cast<SHORT>(newHeight - 1)
		};

		// resize buffer
		checkWinAPI(SetConsoleScreenBufferSize(hConsole, bufferSize), "SetConsoleScreenBufferSize");

		// resize window
		checkWinAPI(SetConsoleWindowInfo(hConsole, TRUE, &windowRect), "SetConsoleWindowInfo");

		// resize framebuffers
		backBuffer.resize(field.width * field.height);

		frontBuffer.resize(field.width * field.height);
	}

	// Получение ближайшего к RGB цвета консоли
	static int rgbToConsoleColor(int r, int g, int b) noexcept
	{
		r = std::clamp(r, 0, 255);
		g = std::clamp(g, 0, 255);
		b = std::clamp(b, 0, 255);

		int bestColor = 0;
		int minDistance = INT32_MAX;

		// ищем ближайший к консольному цвету
		for(int i = 0; i < 16; ++i)
		{
			const auto& c = cRender::consoleColors[i];

			const int dr = r - c.r;
			const int dg = g - c.g;
			const int db = b - c.b;

			const int dist = dr * dr + dg * dg + db * db;

			if(dist < minDistance)
			{
				minDistance = dist;
				bestColor = i;
			}
		}
		return bestColor;
	}
	// Получение ближайшего к RGB цвета консоли
	static int rgbToConsoleColor(const RGBcolor& c) noexcept
	{
		return rgbToConsoleColor(c.r, c.g, c.b);
	}

	// Создание атрибута цветов фон + текст
	//  4 бита - цвет текста, 4 бита - цвет фона
	// @param fg - цвет текста
	// @param bg - цвет фона
	// @return атрибут цветов фон + текст
	static WORD makeColorAttr(int fg, int bg = 0) noexcept
	{
		return static_cast<WORD>(((bg & 0x0F) << 4) | (fg & 0x0F));
	}

	// Запись символа с цветом в буфер
	void putChar(int x, int y, char c, WORD attr)
	{
		//assert(inBounds(x, y));
		if(!inBounds(x, y))
			return;

		const int idx = bufferIndex(x, y);

		backBuffer[idx].Char.AsciiChar = c;
		backBuffer[idx].Attributes = attr;
	}
	// Запись символа с цветом в буфер
	void putChar(int x, int y, char c, RGBcolor fColor, RGBcolor bColor = {0, 0, 0})
	{ 
		putChar(x, y, c, makeColorAttr(rgbToConsoleColor(fColor), rgbToConsoleColor(bColor)));
	}

	// Запись текста с цветом в буфер
	void drawTextInternal(std::string_view text, int x, int y, WORD attr)
	{
		for(size_t i = 0; i < text.size(); ++i)
		{
			putChar(x + static_cast<int>(i), y, text[i], attr);
		}
	}
	// Запись текста с цветом в буфер
	void drawTextInternal(std::string_view text, int x, int y, RGBcolor fColor, RGBcolor bColor = {0, 0, 0})
	{
		drawTextInternal(text, x, y, makeColorAttr(rgbToConsoleColor(fColor), rgbToConsoleColor(bColor)));
	}

public:
	// конструктор (инициализация консоли)
	cRender()
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		assert(hConsole != INVALID_HANDLE_VALUE); //! возможно, что-то получше, ERR?

		checkWinAPI(GetConsoleCursorInfo(hConsole, &originalCursorInfo), "GetConsoleCursorInfo");

		checkWinAPI(GetConsoleScreenBufferInfo(hConsole, &originalScreenInfo), "GetConsoleScreenBufferInfo");

		originalFontInfo.cbSize = sizeof(originalFontInfo);

		checkWinAPI(GetCurrentConsoleFontEx(hConsole, FALSE, &originalFontInfo), "GetCurrentConsoleFontEx");

		//! Задаем параметры вручную (надо бы получать и обсчитывать!) - НАДО ПЕРЕДЕЛАТЬ!
		// Брать базовые параметры и считать хотя бы то, что можно посчитать

		field.width = 49; // размеры поля в БК
		field.height = 32;
		// file://C:\Users\Alex\Documents\prog\matris\prj\user\graph\
		// Link:C:\Users\Alex\Documents\prog\matris\prj\user\graph\prototype.md

		screen.w = field.width; // для консоли - в символах
		screen.h = field.height;

		baseUnit.w = 1;
		baseUnit.h = 1;

		fontSize = 16;

		cubeSize.w = 3;
		cubeSize.h = 1;

		// Задаем размеры
		setSize(screen.w, screen.h);

		// Устанавливаем фонт
		setFont(L"Consolas", fontSize);

		// Убираем курсор
		hideCursor();

		// Очищаем экран
		CHAR_INFO empty {};
		empty.Char.AsciiChar = ' ';
		empty.Attributes = makeColorAttr(7, 0);

		std::fill(frontBuffer.begin(), frontBuffer.end(), empty);
		std::fill(backBuffer.begin(), backBuffer.end(), empty);
	}

	// Деструктор - завершаем работу с консолью
	~cRender()
	{
		// Восстанавливаем курсор
		SetConsoleCursorInfo(hConsole, &originalCursorInfo);

		// Восстанавливаем фонт
		SetCurrentConsoleFontEx(hConsole, FALSE, &originalFontInfo);
	}

	// Исключаем копирование
	cRender(const cRender&) = delete;
	cRender& operator=(const cRender&) = delete;

	////_______________________________________________________________

	// Frame lifecycle

	// Начало нового кадра (очистка буфера нового кадра)
	void beginFrame()
	{
		// Полная очистка backbuffer
		// Намного быстрее и стабильнее, чем system("cls")
		CHAR_INFO empty {};
		empty.Char.AsciiChar = ' ';
		empty.Attributes = makeColorAttr(7, 0);

		std::fill(backBuffer.begin(), backBuffer.end(), empty);
	}

	//! Вывод буфера в консоль - protected!
	void flushRun(int y, int x1, int x2)
	{
		SMALL_RECT rect
		{
			static_cast<SHORT>(x1),
			static_cast<SHORT>(y),
			static_cast<SHORT>(x2),
			static_cast<SHORT>(y)
		};

		COORD bufferSize
		{
			static_cast<SHORT>(field.width),
			static_cast<SHORT>(field.height)
		};

		COORD bufferCoord
		{
			static_cast<SHORT>(x1),
			static_cast<SHORT>(y)
		};

		// Вывод буфера в консоль
		checkWinAPI(WriteConsoleOutputA(hConsole, backBuffer.data(), bufferSize, bufferCoord, &rect), "WriteConsoleOutputA");
	}

	//! Сравнение двух ячеек - protected!
	inline static bool cellEquals(const CHAR_INFO& a, const CHAR_INFO& b) noexcept
	{
		return a.Char.AsciiChar == b.Char.AsciiChar && a.Attributes == b.Attributes;
	}

	// Обновление кадра (отображение обновленного кадра) - public
	void updateFrame()
	{
		SMALL_RECT region {};

		for(int y = 0; y < field.height; ++y)
		{
			int runStart = -1;

			for(int x = 0; x < field.width; ++x)
			{
				const int idx = y * field.width + x;

				if(!cellEquals(backBuffer[idx], frontBuffer[idx]))
				{
					if(runStart < 0)
						runStart = x;
				}
				else
				{
					if(runStart >= 0)
					{
						flushRun(y, runStart, x - 1);
						runStart = -1;
					}
				}
			}

			// хвост строки
			if(runStart >= 0)
			{
				flushRun(y, runStart, field.width - 1);
			}
		}

		frontBuffer.swap(backBuffer);
	}


	// Drawing API - protected
	////_______________________________________________________________

	// вывод текста цветами по умолчанию (светло-серый на черном)
	//void DrawTxt(std::string text, int x, int y) override
	void drawTxt(std::string_view text, int x, int y)
	{
		drawTextInternal(text, x, y, makeColorAttr(7, 0));
	}

	// вывод текста с цветами
	void drawTxtC(std::string_view text, int x, int y, int color, int back = 0)
	{
		drawTextInternal(text, x, y, makeColorAttr(color, back));
	}

	// Рисуем линию - прямой вывод через Безенхема
	void drawLine(int x1, int y1, int x2, int y2, int color, char sym = '*')
	{
		const WORD attr = makeColorAttr(color);

		int dx = abs(x2 - x1);
		int dy = abs(y2 - y1);

		int sx = (x1 < x2) ? 1 : -1;
		int sy = (y1 < y2) ? 1 : -1;

		int err = dx - dy;

		while(true)
		{
			putChar(x1, y1, sym, attr);

			if(x1 == x2 && y1 == y2)
				break;

			int e2 = err * 2;

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
	}


	// Запись игровых объектов в буфер
public:
	// Рисуем стакан
	void drawGlass(int glassW, int glassH, const RGBcolor& color)
	//void DrawGlass() override
	{
		const int c = rgbToConsoleColor(color);

		const int x0 = 1;
		const int y0 = 1; //! а кнопки???

		// левая стенка
		drawLine(x0, y0, x0, y0 + glassH * cubeSize.h, c, '|');

		// правая стенка
		drawLine(x0 + glassW * cubeSize.w + 1, y0, x0 + glassW * cubeSize.w + 1, y0 + glassH * cubeSize.h, c, '|');

		// дно
		drawLine(x0, y0, x0 + glassW * cubeSize.w + 1, y0, c, '-');
	}

	// Рисуем кубик - protected
	void drawCube(const Cube& cube) override
	{
		if(!cube.getVisible()) // если кубик невидимый
			return;
		
		// формируем цвет кубика
		const int color = rgbToConsoleColor(cube.getColor());

		// Считаем сдвиг по X
		const int sx = 1 + 1 + cube.getX() * cubeW; //! нужно использовать угловой пиксель стакана!!!

		// Считаем сдвиг по Y
		const int sy = 1 + 1 + cube.getY() * cubeH; //! нужно использовать угловой пиксель стакана!!!

		// Формируем кубик (текст для вывода)
		const std::string txt =	"[" + std::to_string(cube.getDigit()) + "]";

		// Выводим кубик
		drawTxtC(txt, sx, sy, color);
	}

	// Рисуем фигуру
	void drawFigure(const Figure& figure)
	{
		for(const Cube* cube : figure.getCubes()) // getCubes() возвращает const std::vector<Cube*>&
			drawCube(*cube);
	}

	// Рисуем слои
	void drawLayers() override
	{}

	// Рисуем блок инфо справа (и, возможно - внизу правила в 2 строки?)
	void drawInfo() override
	{}
	
	// Рисуем кнопки снизу
	void drawButtons() override
	{}
};

constexpr std::array<RGBcolor, 16> cRender::consoleColors; // constexpr static