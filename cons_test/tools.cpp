// @file: tools.cpp
//
#include "tools.h"

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
