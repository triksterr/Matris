#pragma once
// @file: c_render.h

// Buffered WinAPI console renderer.
// C++17

// Основные изменения:
// 1. Полностью убран std::cout rendering
// 2. Полностью убран cursor-based rendering
// 3. Добавлен framebuffer через CHAR_INFO
// 4. Добавлен double-buffer-like подход:
//      - рисование в memory buffer
//      - единый Present()
// 5. Убрано мерцание
// 6. Исправлены const/copy/reference проблемы
// 7. Исправлены WinAPI проблемы
// 8. Убран system("cls")
// 9. drawLine() теперь immediate Bresenham
// 10. Исправлена coordinate consistency
// 11. Исправлены color attribute corruption bugs
// 12. Renderer больше НЕ знает Round/Figure layout напрямую
////_______________________________________________________________

#include <windows.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#include "i_render.h"
#include "types.h"
#include "cube.h"
#include "figure.h"

// вывод в консоль Windows
class cRender final : public IRender
{
private:

	// Консоль

	HANDLE hConsole = INVALID_HANDLE_VALUE;

	CONSOLE_CURSOR_INFO originalCursorInfo {};
	CONSOLE_SCREEN_BUFFER_INFO originalScreenInfo {};
	CONSOLE_FONT_INFOEX originalFontInfo {};

	// Задаем параметры вручную (надо бы получать и обсчитывать!)

	int width = 0;
	int height = 0;

	int ScreenW = 75;
	int ScreenH = 33;

	int UnitW = 1;
	int UnitH = 1;

	int FontSize = 16;

	int FieldW = 1;
	int FieldH = 1;

	int cubeW = 3;
	int cubeH = 1;

	// ========================================================
	// Backbuffer
	// ========================================================

	// Основной framebuffer
	// Каждый элемент содержит: символ + цвет
	std::vector<CHAR_INFO> backBuffer;

	// Console palette
	// constexpr palette -> без dynamic allocation.
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

	// ========================================================
	// Helpers
	// ========================================================

	// Преобразование координат renderer -> console.
	// Renderer: (0,0) bottom-left -> Console: (0,0) top-left
	inline int toConsoleY(int y) const noexcept
	{
		return height - y - 1;
	}

	inline bool inBounds(int x, int y) const noexcept
	{
		return
			x >= 0 &&
			y >= 0 &&
			x < width &&
			y < height;
	}

	inline int bufferIndex(int x, int y) const noexcept
	{
		return toConsoleY(y) * width + x;
	}

	// ========================================================
	// WinAPI safe wrappers
	// ========================================================

	void checkWinAPI(BOOL result, const char* msg) const
	{
		if(result)
			return;

		DWORD err = GetLastError();

		// В production:
		//   logger
		//   debugger output
		//   exception
		//
		// Пока assert.

		assert(false && "WinAPI call failed");
		(void)err;
		(void)msg;
	}

	// ========================================================
	// Console setup
	// ========================================================

	void hideCursor() const
	{
		CONSOLE_CURSOR_INFO ci {};

		checkWinAPI(
			GetConsoleCursorInfo(hConsole, &ci),
			"GetConsoleCursorInfo"
		);

		ci.bVisible = FALSE;

		checkWinAPI(
			SetConsoleCursorInfo(hConsole, &ci),
			"SetConsoleCursorInfo"
		);
	}

	void showCursor() const
	{
		CONSOLE_CURSOR_INFO ci {};

		checkWinAPI(
			GetConsoleCursorInfo(hConsole, &ci),
			"GetConsoleCursorInfo"
		);

		ci.bVisible = TRUE;

		checkWinAPI(
			SetConsoleCursorInfo(hConsole, &ci),
			"SetConsoleCursorInfo"
		);
	}

	void setFont(
		const std::wstring& fontName,
		int fontHeight,
		int fontWidth = 0
	) const
	{
		CONSOLE_FONT_INFOEX cfi {};
		cfi.cbSize = sizeof(cfi);

		checkWinAPI(
			GetCurrentConsoleFontEx(
				hConsole,
				FALSE,
				&cfi
			),
			"GetCurrentConsoleFontEx"
		);

		wcscpy_s(cfi.FaceName, fontName.c_str());

		cfi.dwFontSize.X = static_cast<SHORT>(fontWidth);
		cfi.dwFontSize.Y = static_cast<SHORT>(fontHeight);

		checkWinAPI(
			SetCurrentConsoleFontEx(
				hConsole,
				FALSE,
				&cfi
			),
			"SetCurrentConsoleFontEx"
		);
	}

	// ========================================================
	// Resize console
	// ========================================================

	// В WinAPI:
	// buffer >= window
	//
	// Поэтому resize выполняем безопасно.
	void setSize(int newWidth, int newHeight)
	{
		assert(newWidth > 0);
		assert(newHeight > 0);

		width = newWidth;
		height = newHeight;

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

		// 1. Сначала buffer
		checkWinAPI(
			SetConsoleScreenBufferSize(
				hConsole,
				bufferSize
			),
			"SetConsoleScreenBufferSize"
		);

		// 2. Потом window
		checkWinAPI(
			SetConsoleWindowInfo(
				hConsole,
				TRUE,
				&windowRect
			),
			"SetConsoleWindowInfo"
		);

		// Resize framebuffer
		backBuffer.resize(width * height);
	}

	// ========================================================
	// Colors
	// ========================================================

	static int rgbToConsoleColor(int r, int g, int b) noexcept
	{
		r = std::clamp(r, 0, 255);
		g = std::clamp(g, 0, 255);
		b = std::clamp(b, 0, 255);

		int bestColor = 0;
		int minDistance = INT32_MAX;

		// nearest color search
		for(int i = 0; i < 16; ++i)
		{
			const auto& c = consoleColors[i];

			const int dr = r - c.r;
			const int dg = g - c.g;
			const int db = b - c.b;

			const int dist =
				dr * dr +
				dg * dg +
				db * db;

			if(dist < minDistance)
			{
				minDistance = dist;
				bestColor = i;
			}
		}

		return bestColor;
	}

	static int rgbToConsoleColor(
		const RGBcolor& c
	) noexcept
	{
		return rgbToConsoleColor(
			c.r,
			c.g,
			c.b
		);
	}

	static WORD makeColorAttr(
		int fg,
		int bg = 0
	) noexcept
	{
		return static_cast<WORD>(
			((bg & 0x0F) << 4) |
			(fg & 0x0F)
		);
	}

	// ========================================================
	// Backbuffer pixel
	// ========================================================

	void putChar(
		int x,
		int y,
		char c,
		WORD attr
	)
	{
		if(!inBounds(x, y))
			return;

		const int idx = bufferIndex(x, y);

		backBuffer[idx].Char.AsciiChar = c;
		backBuffer[idx].Attributes = attr;
	}

	// ========================================================
	// Internal text draw
	// ========================================================

	void drawTextInternal(
		std::string_view text,
		int x,
		int y,
		WORD attr
	)
	{
		for(size_t i = 0; i < text.size(); ++i)
		{
			putChar(
				x + static_cast<int>(i),
				y,
				text[i],
				attr
			);
		}
	}

public:
	// конструктор (инициализация)
	cRender()
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		assert(hConsole != INVALID_HANDLE_VALUE);

		checkWinAPI(GetConsoleCursorInfo(hConsole, &originalCursorInfo), "GetConsoleCursorInfo");

		checkWinAPI(GetConsoleScreenBufferInfo(hConsole, &originalScreenInfo), "GetConsoleScreenBufferInfo");

		originalFontInfo.cbSize = sizeof(originalFontInfo);

		checkWinAPI(GetCurrentConsoleFontEx(hConsole, FALSE, &originalFontInfo), "GetCurrentConsoleFontEx");
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

	// Инициализация 
	void Init() override
	{
		setSize(ScreenW, ScreenH);

		setFont(L"Consolas", FontSize);

		hideCursor();

		BeginFrame();
		Present();
	}


	// Frame lifecycle
	////_______________________________________________________________

	// 
	void BeginFrame()
	{
		// Полная очистка backbuffer
		// Намного быстрее и стабильнее, чем system("cls").

		CHAR_INFO empty {};
		empty.Char.AsciiChar = ' ';
		empty.Attributes = makeColorAttr(7, 0);

		std::fill(backBuffer.begin(), backBuffer.end(), empty);
	}

	// 
	void Present()
	{
		COORD bufferSize
		{
			static_cast<SHORT>(width),
			static_cast<SHORT>(height)
		};

		COORD bufferCoord {0, 0};

		SMALL_RECT writeRegion
		{
			0,
			0,
			static_cast<SHORT>(width - 1),
			static_cast<SHORT>(height - 1)
		};

		checkWinAPI(WriteConsoleOutputA(hConsole, backBuffer.data(), bufferSize, bufferCoord, &writeRegion), "WriteConsoleOutputA");
	}


	// Drawing API
	////_______________________________________________________________

	// вывод текста цветом по умолчанию
	void DrawTxt(std::string text, int x, int y) override
	{
		drawTextInternal(text, x, y, makeColorAttr(7, 0));
	}

	// вывод текста с цветом
	void DrawTxtC(std::string_view text, int x, int y, int color, int back = 0)
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

	// Game rendering
	////_______________________________________________________________

	// Рисуем стакан
	void drawGlass(int glassW, int glassH, const RGBcolor& color)
	{
		const int c = rgbToConsoleColor(color);

		const int x0 = FieldW;
		const int y0 = FieldH;

		// левая стенка
		drawLine(x0, y0, x0, y0 + glassH * cubeH, c, '|');

		// правая стенка
		drawLine(x0 + glassW * cubeW + 1, y0, x0 + glassW * cubeW + 1, y0 + glassH * cubeH, c, '|');

		// дно
		drawLine(x0, y0, x0 + glassW * cubeW + 1, y0, c, '-');
	}

	// Рисуем кубик
	void drawCube(const Cube& cube) override
	{
		if(!cube.getVisible()) // если кубик невидимый
			return;
		
		// формируем цвет кубика
		const int color = rgbToConsoleColor(cube.getR(), cube.getG(), сube.getB);

		// Считаем сдвиг по X
		const int sx = FieldW + 1 + cube.getX() * cubeW;

		// Считаем сдвиг по Y
		const int sy = FieldH + 1 + cube.getY() * cubeH;

		// Формируем кубик (текст для вывода)
		const std::string txt =	"[" + std::to_string(cube.getNum()) + "]";

		// Выводим кубик
		DrawTxtC(txt, sx, sy, color);
	}

	// Рисуем фигуру
	void drawFigure(const Figure& figure)
	{
		for(const Cube& cube : figure.getCubes())
		{
			drawCube(cube);
		}
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


// constexpr static
////_______________________________________________________________
constexpr std::array<RGBcolor, 16>
cRender::consoleColors;