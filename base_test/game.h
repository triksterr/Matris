#pragma once
// file: game.h

#include "point.h"
#include "round.h"
#include "..\..\!lib\err\err.h"
#include "..\..\!lib\err\err_codes.h"

// Сама игра
class Game
{
public:
	// Удаляем копирование и присваивание
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	// Получение экземпляра синглтона
	static Game& get() //! вынести в CPP файл!
	{
		static Game instance;
		return instance;
	}
	
	// Link:C:\Users\Alex\Documents\prog\matris\base_test\doc\game_loop.md

	// Запуск цикла раундов/уровней в пределах одной игры
	// @param mode - режим запуска (0 - обычный, 1 - тест, ...)
	// @return успех/ошибка, ...
	ErrC start(int mode = 0)
	{
	// Генерация базовых параметров игры
	
	// Пользовательские настройки (из файла/default - и вручную из экрана настроек)
	

	// Запуск цикла раундов
	
	// Прарметры - для каждого раунда:

		// Запуск раунда с передачей параметров
		Round::get().start();

		// 

		return PartImplemented; // все хорошо
	}

	// Установка размеров стакана
	void setGlass(Point sizes)
	{
		gassSizes = sizes;
	}

	// Установка размеров стакана
	void setGlass(int width, int height)
	{
		gassSizes.w = width;
		gassSizes.h = height;
	}

	// Получение размеров стакана
	Point getGlass()
	{
		return gassSizes;
	}

private:
	Point gassSizes = {10, 20}; //! Default 

// singleton
	Game() = default;
	~Game() = default;
};

