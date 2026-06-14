#pragma once
// file: application.h

#include "game.h"
//#include "..\..\!lib\err\err_codes.h"
#include "..\..\!lib\err\err.h"
#include "interface\json.hpp"
#include "interface\i_files.h"


// само приложение
class Application
{
public:
	// Настройки программы и игры
	struct GameSettings
	{
		std::string sig = "Game Matris settings file JSON. 2026";
		uint32_t version = 1; //! ++ при любом изменении структуры
		uint32_t level = 0; // уровень сложности (начальный/текущий)
		std::string userName = "Alumno"; // имя пользователя 
		std::string comment = "Это базовая версия файла настроек: полей настроек нет.";

		//! Изменения полей отразить здесь: link:application.h:NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE

		//TODO ограничение строк по длинне!!!
	};//! gameSettings;

public:
// Удаляем копирование и присваивание
	Application(const Application& other) = delete;
	Application& operator=(const Application& other) = delete;
	// Получение экземпляра синглтона
	static Application& get() //! вынести в CPP файл!
	{
		static Application instance;
		return instance;
	}

	// Запуск игры
	// @param mode - режим запуска
	// @return успех/ошибка, ...
	ErrC start(int mode = 0)
	{
		// TODO Работа с файлом настроек
		// https://chatgpt.com/c/6a1b0ab2-720c-83eb-ab97-542d8f0eeefe
		// Link:.\interface\i_files.h
		// 

		
		// Пользовательские настройки (из файла/default - и вручную из экрана настроек)
		// Генерация базовых параметров игры




		// Инициализируем параметры и правила игры в соответствии с текущими/заданными настройками игры

		// Link:C:\Users\Alex\Documents\prog\matris\base_test\doc\game_loop.md



		// Запускаем саму игру с передачей настроек
		//Game::get().start();

		//RETURN_ERROR_SIMPLE(Game::get().start(), "Game::get().start()");

		// Игра закончена: победа/поражение

		// Новая игра?

		// Выход

		return PartImplemented; // все нормально
	}

private:
	// singleton
	Application() = default;
	~Application() = default;
};

// Макрос для автоматической сериализации/десериализации
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Application::GameSettings, sig, version, level, userName, comment)