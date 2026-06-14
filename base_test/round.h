#pragma once
// file: round.h

// Один раунд игры
class Round
{
public:
	// Удаляем копирование и присваивание
	Round(const Round& other) = delete;
	Round& operator=(const Round& other) = delete;
	// Получение экземпляра синглтона
	static Round& get() //! вынести в CPP файл!
	{
		static Round instance;
		return instance;
	}
	
	// Запуск раунда
	// @param mode - режим запуска
	// @return успех/ошибка, ...
	int start(int mode = 0)
	{
	// Инициализируем параметры и правила раунда в соответствии с настройками игры:

	// Возможно - переносим заполнение слоев из предыдущего раунда (если singletone - просто не стираем)

	// Link:C:\Users\Alex\Documents\prog\matris\base_test\doc\game_loop.md

	// Цикл:
	// - Создание новой фигуры (если сразу касание слоев или перечесение со слоями -> переход фигуры в слои -> игра окончена)
	// - Движение фигуры (если касание слоев -> переход фигуры в слои)
	// - Удаление фигуры - move кубиков из фигуры в слои
	// - Удаление кубиков в слоях по правилам раунда
	// - Возврат к Созданию новой фигуры


	// Параметры - для фигур:


		return 0; // все ок
	}

private:
	// singleton
	Round() = default;
	~Round() = default;
};

