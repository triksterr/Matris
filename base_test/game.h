#pragma once
// file: game.h

// Сама игра
class game
{
public:
	// Удаляем копирование и присваивание
	game(const game& other) = delete;
	game& operator=(const game& other) = delete;
	// Получение экземпляра синглтона
	static game& get()
	{
		static game instance;
		return instance;
	}
	
	// Генерация базовых параметров игры
	// Пользовательские настройки (из файла/default - и вручную)
	// Запуск цикла раундов


	// Прарметры - для раунда:

private:
// singleton
	game() = default;
	~game() = default;
};

