#pragma once
// @file: i_files.h

#include <string>
#include <vector>

#include "..\..\..\!lib\err\err_codes.h"

#include "..\application.h"

//универсальный доступ через интерфейс
//auto fm = fileMan();   // получаем указатель на iFiles

//! Убрать комментарий внизу: //!protected: // Нижний уровень  _________________________________________________________

// Интерфейс работы с файлами
class iFiles
{
public:
	virtual ~iFiles() = default;

	// Заргузка настроек, счета, текущего состояния
	ErrC loadSettings(Application::gameSettings &settings)
	{
		if(exists("settings.json") != ErrC::Ok)
		{
			//saveSettings(); // запись текущих настроек
		}

		// Если файл существует
		// - читаем в буфер
		// - распознаем JSON
		// - преобразуем в структуру

		// сравниваем версии

		// Если версии не совпадают
			// сравниваем поля

		return NotImplemented; // метод не реализован
	}

	//Поведение Load():
	//1. Создать Settings при запуске программы (там уже лежат значения по умолчанию)
	//2. Открыть и распознать JSON - в другую копию структуры настроек
	//	Сравнить версии настроек.
	//	Если версии - все ок.
	//	Если версия файла старее - считать из файла в новый блок настроек только старые поля - с учетом правил, которые могут определять зависимости между полями
	//	Если версия файла новее - считать из файла только те поля, которые соответствуют версии настроек (возможно, с учетом правил). В крайнем случае - просто игнорировать неизвестные поля. И сохнанение файла выполнить по формату актуальной версии настроек.

	// Запись настроек, счета, текущего состояния
	ErrC saveSettings(const Application::gameSettings &settings)
	{
		// Берем структуру настроек
		// - преобразeм в JSON
		// Просто пишем в файл
		// И смотрим на реакцию - на ошибки

		return NotImplemented; // метод не реализован
	}

	// Загрузка текущего состояния игры
	ErrC loadState()
	{
		return NotImplemented; // метод не реализован
	}

	ErrC saveState()
	{
		return NotImplemented; // метод не реализован
	}

	// загрузка достижений
	ErrC loadResults()
	{
		return NotImplemented; // метод не реализован
	}

	ErrC saveResults()
	{
		return NotImplemented; // метод не реализован
	}

	// Загрузка локализации
	ErrC loadLocalization()
	{
		return NotImplemented; // метод не реализован
	}

	// Загрузка музыки - ????
	ErrC loadMusic()
	{
		return NotImplemented; // метод не реализован
	}

	// Загрузка звука/музыки - читаем бинарный файл и преобразуем его в звуковой поток
	ErrC loadSound()
	{
		return NotImplemented; // метод не реализован
	}

	// Загрузка картинки - читаем бинарный файл
	ErrC loadImage()
	{
		return NotImplemented; // метод не реализован
	}

//!protected: // Нижний уровень  _________________________________________________________

	// чтение в JSON
	ErrC readJSON(const std::string name) // нужна ссылка на структуру в параметрах
	{
		// - читаем из файла текст в Буфер readText(
		// - проверяем на соответствие JSON
		// - преобразeм в структуру
		
		
		return NotImplemented; // метод не реализован
	}

	// запись в JSON
	ErrC writeJSON(const std::string name)
	{
		// Берем структуру
		// - преобразeм в JSON
		// - пишем в буфер
		// - Пишем буфер в файл
		
		return NotImplemented; // метод не реализован
	}

	// Проверка существования файла
	virtual ErrC exists(const std::string& path) const = 0;

	// Чтение текста
	virtual ErrC readText(const std::string& path, std::string& text) const = 0;

	// Запись текста
	virtual ErrC writeText(const std::string& path, const std::string& text) = 0;

	// Чтение данных
	virtual ErrC readBinary(const std::string& path, std::vector<uint8_t>& data) const = 0;

	// Запись данных
	virtual ErrC writeBinary(const std::string& path, const std::vector<uint8_t>& data) = 0;
};

// фабричный метод
std::unique_ptr<iFiles> fileMan();
// универсальный доступ через интерфейс:
//auto fm = fileMan();   // получаем указатель на iFiles
