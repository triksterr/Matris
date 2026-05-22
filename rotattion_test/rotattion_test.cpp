// file: rotattion_test.cpp

#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <windows.h>

#include "../cons_test/types.h" // class Point

// Алгоритм Брезенхема
// @param x0, y0 - начальная точка
// @param x1, y1 - конечная точка
// @param out - результат: вектор точек
static void Bresenham( int x0, int y0, int x1, int y1, std::set<Point>& out)
{
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while(true)
    {
        out.insert({ x0, y0 });

        if(x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if(e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if(e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

// Рисование дуги
// @param xc, yc - центр окружности
// @param x1, y1 - начальная точка дуги
// @param alpha - угол
// @return - вектор точек
std::vector<Point> RasterArc( int xc, int yc, int x1, int y1,  double alpha)
{
    std::set<Point> pixels;

    double dx = x1 - xc;
    double dy = y1 - yc;

    double r = std::sqrt(dx * dx + dy * dy);

    double phi0 = std::atan2(dy, dx);

    double step; // Безопасный угловой шаг

    if(r < 1e-9)
        step = std::abs(alpha);
    else
        step = 2.0 * std::asin(0.25 / r);

    if(step < 1e-6)
        step = 1e-6;

    int segments = (((1) > ((int)std::ceil(std::abs(alpha) / step))) ? (1) : ((int)std::ceil(std::abs(alpha) / step)));

    double dphi = alpha / segments;

    int prevX = x1;
    int prevY = y1;

    pixels.insert({ prevX, prevY });

    for(int i = 1; i <= segments; ++i)
    {
        double a = phi0 + dphi * i;

        double fx = xc + r * std::cos(a);
        double fy = yc + r * std::sin(a);

        int x = (int)std::lround(fx);
        int y = (int)std::lround(fy);

        Bresenham(prevX, prevY, x, y, pixels);

        prevX = x;
        prevY = y;
    }

    return std::vector<Point>(pixels.begin(), pixels.end()); // преобразование в вектор
}

// установка курсора в консоли
// @param x, y - координаты
void gotoxy(int x, int y)
{

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(hConsole, coord);
}

// прямой вывод в консоль
// @param x, y - координаты вывода символа
// @param c - символ
static void consPrint(int x, int y, char c)
{
	gotoxy(x, y);
	std::cout << c;
}

// Перевод градусов в радианы
double toRad(double degrees) { return degrees * M_PI / 180.0f; }

// Перевод радиан в градусы
double toDeg(double radians) { return radians * 180.0f / M_PI; }

//! В идеале: по каждому кубику фигуры - получаем точки дуги, затем получаем точки радиуса в каждую точку дуги и все точки всех радиусов проверяем
//! И еще хорошо бы прибавить к радиусу 1 - чтобы точно ничего не коснуться

//TODO Проверка поворота кубика на задевание им кубиков нижних слоёв при повороте
bool chkRotateCube(); // параметры: кубик, угол поворота



// получаем координаты центрального кубика - смещение для расчета абсолютных координат в стакане???
// Нужно получить координаты центрального кубика в стакане

std::vector<Point> RasterArc2(int xc, int yc, int x1, int y1, double angle)
{

// Считаем длину вектора от центра центрального кубика до центра этого кубика
//float radius = ;

	int angleInt = (int)angle; // считаем целую часть angle
    double angleFrac = angle - angleInt; // считаем дробную часть angle
    angle = angleFrac + (((angleInt % 360) + 360) % 360); // убираем лишние обороты

    //x Считаем угол вектора (начальный угол этого кубика) - не факт, что это надо!
    //! Конечный угол - считается по формуле поворота - от координат кубика
    // Определяем направление поворота: по часовой (направо)
    //		+90/-270
    // или против часовой (налево)
    //		-90/+270
    // Определяем квадрант:
    // 		I : x>=0, y>0
    // 		II: x<0, y>=0
    // 		III: x<=0, y<0
    // 		IV : x>0, y<=0
    // На основе квадранта и направления поворота - определяем ведущую координату поворота:
    // - По часовой:
    // 		I : y
    // 		II: x
    // 		III: y
    // 		IV : x
    // - По против часовой:
    // 		I : x
    // 		II: y
    // 		III: x
    // 		IV : y

    // Исходя из конечного угла поворота (конечных координат) определяем конечное значение ведущей координаты
    // Проходим по ведущей координате от начального до конечного значения c шагом 1
    // Каждый раз определяем значение ведомой координаты по теореме Пифагора
    //		Прибавляем к ней 0,5 и округляем вверх - в каждой целочисленной точке поворота этого вектора
    //		Это будут координаты кубика, который может помешать повороту
    //		Если там есть кубик - поворот невозможен
}

//! Проверка на всем массиве нижних слоев

//! Проверка на вылет за края при повороте!!!

//! Прокатать здесь мой алгоритм!

int main()
{
    int xc = 10;
    int yc = 20;

    int x1 = 10;
    int y1 = 26;

    double alpha = toRad(180);

    auto pts = RasterArc(xc, yc, x1, y1, alpha);

    consPrint(xc, yc, '0');

    for(auto& p : pts)
    {
        //std::cout << p.x << " " << p.y << "\n";
        consPrint(p.x, p.y, '*');
    }


}