#pragma once
// @file: tools.h
//

#include <random>
#include <time.h>
#include <chrono>


// Вспомогательные функции

// Инициализация генератора случайных чисел
std::mt19937 &initRnd();

// Получение случайного значения
// @param left, right - границы диапазона выдаваемых значений
int getRnd(int left, int right);
