// file: cube.cpp

#include "cube.h"
#include "layers.h"

// Проверка касания кубика нижних слоев
// @return true - если снизу есть кубик
bool Cube::contactLayersB() const
{
	Layers& layers = Layers::getInstance(); // получаем слои

	return Layers::getInstance().isBelow(this); // проверяем наличие в слоях снизу кубика
}