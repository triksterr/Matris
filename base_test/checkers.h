#pragma once

#include "point.h"
#include "..\..\!lib\err\err.h"

#include "cube.h"
#include "figure.h"
#include "game.h"
#include "round.h"

// Проверка наличия кубика в слоях
// @param coord - координаты
ErrC checkCubeL(Point coord);

// Проверка наличия кубика в фигуре
// @param coord - координаты
ErrC checkCubeFL(Point coord);

// Проверка перемещения по всей траектории
// @param from - исходные координаты
// @param to - конечные координаты
ErrC checkMove(Point from, Point to);