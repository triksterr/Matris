В Windows API (Windows.h) есть множество графических функций для работы с устройством контекста (Device Context - HDC). Вот основные категории и функции:

## 1. **Рисование примитивов**

### Линии:
```cpp
// Рисует линию от текущей позиции до указанной
LineTo(HDC hdc, int x, int y);

// Перемещает текущую позицию
MoveToEx(HDC hdc, int x, int y, LPPOINT lpPoint);

// Рисует линию между двумя точками
// (фактически комбинация MoveToEx и LineTo)
```
```cpp
MoveToEx(hdc, 10, 10, NULL);
LineTo(hdc, 100, 100);
```

### Прямоугольники:
```cpp
// Рисует прямоугольник
Rectangle(HDC hdc, int left, int top, int right, int bottom);

// Рисует прямоугольник со скругленными углами
RoundRect(HDC hdc, int left, int top, int right, int bottom, 
          int width, int height);

// Рисует эллипс, вписанный в прямоугольник
Ellipse(HDC hdc, int left, int top, int right, int bottom);

// Рисует дугу (часть эллипса)
Arc(HDC hdc, int left, int top, int right, int bottom,
    int xStartArc, int yStartArc, int xEndArc, int yEndArc);

// Рисует сектор (заполненную дугу)
Pie(HDC hdc, int left, int top, int right, int bottom,
    int xStartArc, int yStartArc, int xEndArc, int yEndArc);
```

### Многоугольники:
```cpp
// Рисует многоугольник
Polygon(HDC hdc, const POINT* points, int count);

// Рисует ломаную линию
Polyline(HDC hdc, const POINT* points, int count);

// Рисует несколько ломаных линий
PolyPolyline(HDC hdc, const POINT* points, 
             const DWORD* polyPoints, int count);
```

## 2. **Работа с цветами и кистями**

```cpp
// Установка цвета текста (для TextOut и DrawText)
SetTextColor(HDC hdc, COLORREF color);

// Установка цвета фона текста
SetBkColor(HDC hdc, COLORREF color);

// Установка режима фона
SetBkMode(HDC hdc, int mode); // OPAQUE или TRANSPARENT

// Создание и выбор кисти
HBRUSH CreateSolidBrush(COLORREF color);
HBRUSH CreateHatchBrush(int hatchStyle, COLORREF color);
HBRUSH CreatePatternBrush(HBITMAP hbmp);
SelectObject(HDC hdc, HBRUSH hBrush);

// Создание и выбор пера
HPEN CreatePen(int style, int width, COLORREF color);
SelectObject(HDC hdc, HPEN hPen);

// Получение и установка пикселя
COLORREF GetPixel(HDC hdc, int x, int y);
BOOL SetPixelV(HDC hdc, int x, int y, COLORREF color); // быстрее чем SetPixel
```

## 3. **Вывод текста**

```cpp
// Простой вывод текста
TextOut(HDC hdc, int x, int y, LPCSTR text, int length);

// Вывод текста с форматированием
DrawText(HDC hdc, LPCSTR text, int length, 
         LPRECT rect, UINT format);

// Расширенный вывод текста
ExtTextOut(HDC hdc, int x, int y, UINT options, 
           const RECT* rect, LPCSTR text, UINT length, 
           const INT* dx);

// Установка шрифта
HFONT CreateFont(int height, int width, int escapement, 
                 int orientation, int weight, DWORD italic, 
                 DWORD underline, DWORD strikeOut, 
                 DWORD charSet, DWORD outputPrecision, 
                 DWORD clipPrecision, DWORD quality, 
                 DWORD pitchAndFamily, LPCSTR face);
SelectObject(HDC hdc, HFONT hFont);
```

## 4. **Работа с изображениями (Bitmaps)**

```cpp
// Загрузка изображения
HBITMAP LoadBitmap(HINSTANCE hInstance, LPCSTR name);

// Создание bitmap в памяти
HBITMAP CreateCompatibleBitmap(HDC hdc, int width, int height);

// Копирование изображения
BitBlt(HDC hdcDest, int xDest, int yDest, int width, int height,
       HDC hdcSrc, int xSrc, int ySrc, DWORD rop);

// Растянутое копирование
StretchBlt(HDC hdcDest, int xDest, int yDest, int widthDest, int heightDest,
           HDC hdcSrc, int xSrc, int ySrc, int widthSrc, int heightSrc,
           DWORD rop);

// Прозрачное копирование
TransparentBlt(HDC hdcDest, int xDest, int yDest, int widthDest, int heightDest,
               HDC hdcSrc, int xSrc, int ySrc, int widthSrc, int heightSrc,
               UINT transparentColor);

// Альфа-смешение
AlphaBlend(HDC hdcDest, int xDest, int yDest, int widthDest, int heightDest,
           HDC hdcSrc, int xSrc, int ySrc, int widthSrc, int heightSrc,
           BLENDFUNCTION blendFunction);
```

## 5. **Регионы и пути (Regions & Paths)**

```cpp
// Работа с регионами
HRGN CreateRectRgn(int left, int top, int right, int bottom);
HRGN CreateEllipticRgn(int left, int top, int right, int bottom);
FillRgn(HDC hdc, HRGN hrgn, HBRUSH hbrush);
FrameRgn(HDC hdc, HRGN hrgn, HBRUSH hbrush, int width, int height);

// Работа с путями (paths)
BeginPath(HDC hdc);
// ... рисуем примитивы ...
EndPath(HDC hdc);
StrokePath(HDC hdc);    // обвести путь
FillPath(HDC hdc);      // заполнить путь
StrokeAndFillPath(HDC hdc); // и обвести и заполнить
```

## 6. **Координатные преобразования**

```cpp
// Установка режима отображения
SetMapMode(HDC hdc, int mode); // MM_TEXT, MM_ISOTROPIC и др.

// Масштабирование
SetViewportExtEx(HDC hdc, int x, int y, LPSIZE size);
SetWindowExtEx(HDC hdc, int x, int y, LPSIZE size);

// Смещение
SetViewportOrgEx(HDC hdc, int x, int y, LPPOINT point);
SetWindowOrgEx(HDC hdc, int x, int y, LPPOINT point);
```

## 7. **Другие полезные функции**

```cpp
// Заливка области
FillRect(HDC hdc, const RECT* rect, HBRUSH hbrush);
FrameRect(HDC hdc, const RECT* rect, HBRUSH hbrush);
InvertRect(HDC hdc, const RECT* rect);

// Рисование фокуса
DrawFocusRect(HDC hdc, const RECT* rect);

// Рисование кнопки
DrawEdge(HDC hdc, LPRECT rect, UINT edge, UINT flags);
DrawFrameControl(HDC hdc, LPRECT rect, UINT type, UINT state);

// Очистка области
PatBlt(HDC hdc, int x, int y, int width, int height, DWORD rop);
```

## Пример комплексного использования:

```cpp
#include <windows.h>

void DrawGraphics(HDC hdc) {
    // Устанавливаем перо и кисть
    HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    
    // Рисуем прямоугольник
    Rectangle(hdc, 50, 50, 200, 150);
    
    // Меняем кисть на штриховую
    HBRUSH hHatchBrush = CreateHatchBrush(HS_CROSS, RGB(0, 0, 255));
    SelectObject(hdc, hHatchBrush);
    
    // Рисуем эллипс
    Ellipse(hdc, 250, 50, 400, 150);
    
    // Рисуем многоугольник
    POINT points[] = {{100, 200}, {150, 250}, {200, 200}, {150, 150}};
    Polygon(hdc, points, 4);
    
    // Выводим текст
    SetTextColor(hdc, RGB(128, 0, 128));
    SetBkMode(hdc, TRANSPARENT);
    TextOut(hdc, 300, 200, "Hello Windows API!", 19);
    
    // Восстанавливаем старые объекты
    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);
    
    // Удаляем созданные объекты
    DeleteObject(hPen);
    DeleteObject(hBrush);
    DeleteObject(hHatchBrush);
}
```

## Полезные константы для операций растровых операций (ROP):

```cpp
// Часто используемые ROP-коды для BitBlt:
BLACKNESS = 0x00000042;     // Все черное
WHITENESS = 0x00FF0062;     // Все белое
SRCCOPY = 0x00CC0020;       // Копировать источник
SRCPAINT = 0x00EE0086;      // ИЛИ источника и назначения
SRCAND = 0x008800C6;        // И источника и назначения
SRCINVERT = 0x00660046;     // XOR источника и назначения
```

Эти функции являются частью **GDI (Graphics Device Interface)** - основного графического API в Windows для 2D-графики. Для современной графики также есть **GDI+** (более продвинутый) и **Direct2D** (аппаратно-ускоренный).