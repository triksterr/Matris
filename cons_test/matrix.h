#pragma once
// @file: matrix.h
//

#include <vector>
#include "cube.h"
#include "round.h"



// Матрица всех кубиков в стакане
class Matrix final
{
public:
	// Удаляем копирование и присваивание
	Matrix(const Matrix& other) = delete;
	Matrix& operator=(const Matrix& other) = delete;

	// Получение экземпляра синглтона
	static Matrix &getInstance()
	{
		static Matrix instance;
		return instance;
	}

	// Инициализация матрицы
	void Init() 
	{
		data.clear(); // сброс вектора

		Round &round = Round::getInstance(); // получаем раунд
		data.resize(round.getGlassW() * round.getGlassH(), nullptr); // задание размера и очистка вектора
	}

	// Получение элемента матрицы
	Cube *get(int x, int y)
	{
		Round &round = Round::getInstance(); // получаем раунд
		return data.at(y * round.getGlassW() + x);
	}

	// Запись кубика в матрицу
	void set(Cube *cube)
	{
		Round &round = Round::getInstance(); // получаем раунд
		data.at(cube->getY() * round.getGlassW() + cube->getX()) = cube; // записываем указатель на кубик в матрицу
	}

private:
	// Приватный конструктор и деструктор
	Matrix() = default;
	~Matrix() = default;

	std::vector<Cube *> data; //! вектор указателей на кубики
};