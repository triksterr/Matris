#pragma once
// @file: matrix.h
//

#include <vector>
#include "cube.h"
#include "round.h"

//! Возможно матрица и не нужна
//! В любом случае, запись в нее идет из фигуры и из слоев - там делаются все проверки

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

	// Получение элемента матрицы - указателя на кубик
	// @param x - координата Х (0 - слева)
	// @param y - координата Y (0 - снизу)
	// @return указатель на кубик
	Cube *get(int x, int y) { return data.at(y * Round::getInstance().getGlassW() + x); }

	// Запись кубика в матрицу
	void set(Cube *cube) { data.at(cube->getY() * Round::getInstance().getGlassW() + cube->getX()) = cube;} // записываем указатель на кубик в матрицу

	// Удаление кубика из матрицы
	// @param x - координата Х (0 - слева)
	// @param y - координата Y (0 - снизу)
	void del(int x, int y) { data.at(y * Round::getInstance().getGlassW() + x) = nullptr; }

private:
	// Приватный конструктор и деструктор
	Matrix() = default;
	~Matrix() = default;

	std::vector<Cube *> data; //! вектор указателей на кубики
};