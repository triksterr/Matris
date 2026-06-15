#pragma once
// @file: i_files.h

#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <filesystem>
#include <fstream>
#include <sstream>


#include "json.hpp" // Используем: https://github.com/nlohmann/json  version 3.12.0
#include "..\..\..\!lib\err\err.h"
#include "..\application.h"

// NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Class::testStr, id, name, value) - преобразование testStr из класса Class с заданными полями  в JSON

//универсальный доступ через интерфейс
//auto fm = fileMan();   // получаем указатель на iFiles

//! Убрать комментарий внизу: //!protected: // Нижний уровень  _________________________________________________________

// Интерфейс работы с файлами
class iFiles
{
public:
	virtual ~iFiles() = default;

	// Заргузка настроек
	ErrC loadSettings(Application::GameSettings& settings)
	{
		const std::string path = "settings.json"; // путь можно параметризовать, если нужно

		// Файл не существует -> запись default
		if(fExists(path) != ErrC::Ok) 
		{
			nlohmann::json default_json = settings;   // сериализуем текущую структуру (она уже содержит значения по умолчанию)
			ErrC err = writeJSONWithRetry(path, default_json);
			if(err != ErrC::Ok)
				return err;
			// settings уже является дефолтным, ничего менять не нужно
			return ErrC::Ok;
		}

		// Чтение и парсинг JSON из файла
		nlohmann::json file_json;
		ErrC read_err = readJSONRaw(path, file_json);
		if(read_err != ErrC::Ok) 
		{
			// ошибка чтения или парсинга -> бэкап, сброс
			backupFile(path, ".corrupted");
			nlohmann::json default_json = settings;
			ErrC write_err = writeJSONWithRetry(path, default_json);
			if(write_err != ErrC::Ok)
				return write_err;
			// settings остаётся дефолтным
			return ErrC::ResetToDefault;
		}

		// Проверка сигнатуры
		nlohmann::json default_json = settings;
		if(!file_json.contains("signature") || file_json["signature"] != default_json["signature"]) 
		{
			// бэкап
			backupFile(path, ".bad_sig");
			ErrC write_err = writeJSONWithRetry(path, default_json);
			if(write_err != ErrC::Ok)
				return write_err;
			return ErrC::ResetToDefault;
		}

		// Проверка наличия поля version
		if(!file_json.contains("version")) 
		{
			// сброс без бэкапа
			ErrC write_err = writeJSONWithRetry(path, default_json);
			if(write_err != ErrC::Ok)
				return write_err;
			return ErrC::Ok;
		}

		int file_version = file_json["version"];
		int prog_version = default_json["version"];

		// Если версии совпадают
		if(prog_version == file_version) 
		{
			// Проверяем каждое поле default_json
			bool mismatch = false;
			for(auto& [key, default_val] : default_json.items()) 
			{
				if(!file_json.contains(key)) 
				{
					file_json[key] = default_val;   // добавляем отсутствующее поле
				}
				else 
				{
					if(file_json[key].type() != default_val.type()) 
					{
						mismatch = true;
						break;
					}
				}
			}
			if(mismatch) 
			{
				backupFile(path, ".type_mismatch");
				ErrC write_err = writeJSONWithRetry(path, default_json);
				if(write_err != ErrC::Ok)
					return write_err;
				return ErrC::ResetToDefault;
			}
			// Все проверки пройдены, загружаем данные из файла в settings
			try 
			{
				settings = file_json.get<Application::GameSettings>();
			}
			catch(const nlohmann::json::exception&) 
			{
				return ErrC::JsonIncorrectStructure;
			}
			return ErrC::Ok;
		}

		// Программа новее, чем файл (апгрейд)
		if(prog_version > file_version) 
		{
			nlohmann::json result = default_json; // копия дефолта
			// Проходим по всем полям файла
			for(auto& [key, value] : file_json.items()) 
			{
				if(result.contains(key)) 
				{
					if(value.type() == result[key].type()) 
					{
						result[key] = value;
					}
					else 
					{
						backupFile(path, ".type_mismatch");
						ErrC write_err = writeJSONWithRetry(path, default_json);
						if(write_err != ErrC::Ok)
							return write_err;
						return ErrC::ResetToDefault;
					}
				}
				else 
				{
				 // Лишнее поле в старом файле -> ошибка БЕЗ бэкапа
					ErrC write_err = writeJSONWithRetry(path, default_json);
					if(write_err != ErrC::Ok)
						return write_err;
					return ErrC::ResetToDefault;
				}
			}
			// Запись обновлённой структуры
			ErrC write_err = writeJSONWithRetry(path, result);
			if(write_err != ErrC::Ok)
				return write_err;
			// Загружаем result в settings
			try 
			{
				settings = result.get<Application::GameSettings>();
			}
			catch(const nlohmann::json::exception&) 
			{
				return ErrC::JsonIncorrectStructure;
			}
			return ErrC::Ok;
		}

		// Файл новее чем программа (даунгрейд)
		if(prog_version < file_version) 
		{
			backupFile(path, ".v" + std::to_string(file_version));
			nlohmann::json result = default_json;
			for(auto& [key, default_val] : default_json.items()) 
			{
				if(file_json.contains(key) && file_json[key].type() == default_val.type()) 
				{
					result[key] = file_json[key];
				}
				else if(file_json.contains(key)) 
				{
					// несовпадение типов: сброс (бэкап уже сделан)
					ErrC write_err = writeJSONWithRetry(path, default_json);
					if(write_err != ErrC::Ok)
						return write_err;
					return ErrC::ResetToDefault;
				}
			}
			ErrC write_err = writeJSONWithRetry(path, result);
			if(write_err != ErrC::Ok)
				return write_err;
			try 
			{
				settings = result.get<Application::GameSettings>();
			}
			catch(const nlohmann::json::exception&) 
			{
				return ErrC::JsonIncorrectStructure;
			}
			return ErrC::Ok;
		}

		return ErrC::Ok;
	}

	// Запись настроек, счета, текущего состояния
	ErrC saveSettings(const Application::GameSettings& settings)
	{
		const std::string path = "settings.json";
		nlohmann::json j = settings; // сериализация (макрос NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE - для стуктуры GameSettings)
		return writeJSONWithRetry(path, j);
	}

	// Загрузка текущего состояния игры
	ErrC loadState()
	{
		// читаем JSON

		//! логику!

		return NotImplemented; // метод не реализован
	}

	ErrC saveState()
	{
		// пишем JSON
		return NotImplemented; // метод не реализован
	}

	// загрузка достижений/счета
	ErrC loadResults()
	{
		// читаем JSON

		//! логику!

		return NotImplemented; // метод не реализован
	}

	ErrC saveResults()
	{
		// пишем JSON
		return NotImplemented; // метод не реализован
	}

	// Загрузка локализации
	ErrC loadLocalization()
	{
		// читаем JSON
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

friend int main(); //! для тестирования!
friend void testSaveSettings(iFiles* fm);
friend void testBackupFile(iFiles* fm);
friend void testReadJSONRaw(iFiles* fm);
friend void testLoadSettingsScenarios(iFiles* fm);

protected: // Нижний уровень  _________________________________________________________
	
	// Чтение любого JSON в структуру nlohmann::json
	// @param path - путь к файлу
	// @param outJson - ссылка на структуру
	ErrC readJSONRaw(const std::string& path, nlohmann::json& outJson) const
	{
		std::string text;
		ErrC err = readText(path, text);
		if(err != ErrC::Ok)
			return err;

		try 
		{
			outJson = nlohmann::json::parse(text);
		}
		catch(const nlohmann::json::parse_error&) 
		{
			return ErrC::JsonParseFailed;
		}
		catch(...) 
		{
			return ErrC::UnknownError;
		}
		return ErrC::Ok;
	}

	// Создание бэкапа
	// @param path - путь к файлу
	// @param suffix - суффикс имени бэкап-файла
	virtual ErrC backupFile(const std::string& path, const std::string& suffix)
	{
		using namespace std::chrono;
		auto now = system_clock::now();
		auto ms = duration_cast<milliseconds>(now.time_since_epoch());
		auto sec = duration_cast<seconds>(ms);
		time_t t = sec.count();
		struct tm tm_buf;

		#ifdef _WIN32
		localtime_s(&tm_buf, &t);
		#else
		localtime_r(&t, &tm_buf);
		#endif

		char time_str[20];
		strftime(time_str, sizeof(time_str), "%Y%m%d_%H%M%S", &tm_buf);
		std::string backup_path = path + "." + time_str + suffix;

		// Читаем исходный файл (даже если он повреждён, читаем как есть)
		std::string content;
		if(readText(path, content) == ErrC::Ok) 
		{
			return writeText(backup_path, content);
		}
		else 
		{
			return ErrC::Ok; // Если не удалось прочитать, бэкап не делаем, но и не мешаем работе
		}
	}

	// Запись JSON в файл с несколькими повторами
	// @param path - путь к файлу
	// @param data - ссылка на структуру
	// @param retries - количество повторов
	ErrC writeJSONWithRetry(const std::string& path, const nlohmann::json& data, int retries = 3)
	{
		// Используем error_handler_t::replace для избежания исключений из-за некорректного UTF-8
		std::string content = data.dump(4, ' ', false, nlohmann::json::error_handler_t::replace);  // 4 - отступы для читаемости

		for(int attempt = 0; attempt < retries; ++attempt) 
		{
			ErrC err = writeText(path, content);
			if(err == ErrC::Ok)
				return ErrC::Ok;

			if(attempt == retries - 1)
				return ErrC::FileWriteFailed; // последняя попытка не удалась

			// Задержка: перед последней попыткой 1 секунда, иначе 0.1 сек
			if(attempt == retries - 2)
				std::this_thread::sleep_for(std::chrono::seconds(1));
			else
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		return ErrC::FileWriteFailed;
	}

	// Чтение JSON из файла и десериализация в переданную структуру
	// @param path - путь к файлу
	// @param dataStruct - ссылка на структуру
	// @return код ошибки ErrC
	template<typename T>
	ErrC readJSON(const std::string& path, T& dataStruct) const
	{
		std::string text;
		ErrC err = readText(path, text); // Читаем текст из файла

		if(err != ErrC::Ok)
			return ErrC::FileNotFound;  // Файл не существует

		try
		{
			// Парсим JSON и заполняем структуру
			nlohmann::json j = nlohmann::json::parse(text);
			dataStruct = j.get<T>();
		}
		catch(const nlohmann::json::parse_error&)
		{
			return ErrC::JsonParseFailed;    // Некорректный JSON
		}
		catch(const nlohmann::json::type_error&)
		{
			return ErrC::JsonIncorrectStructure;  // JSON не соответствует структуре
		}
		catch(...)
		{
			return ErrC::UnknownError;
		}

		return ErrC::Ok;
	}

	// Сериализация структуры в JSON и запись в файл
	// @param path - путь к файлу
	// @param dataStruct - ссылка на структуру
	// @return код ошибки ErrC
	template<typename T>
	ErrC writeJSON(const std::string& path, const T& dataStruct)
	{
		try
		{
			nlohmann::json j = dataStruct;          // использует ADL to_json
			std::string text = j.dump(4);      // отступы для читаемости
			return writeText(path, text);
		}
		catch(const nlohmann::json::exception&)
		{
			return ErrC::SerializationError;
		}
		catch(...)
		{
			return ErrC::UnknownError;
		}
	}

	// Специфические для конкретной OS реализации:

	// Проверка существования файла
	virtual ErrC fExists(const std::string& path) const = 0;

	// Чтение текста
	virtual ErrC readText(const std::string& path, std::string& text) const = 0;

	// Запись текста
	virtual ErrC writeText(const std::string& path, const std::string& text) = 0;

	// Чтение байтовых данных
	virtual ErrC readBinary(const std::string& path, std::vector<uint8_t>& data) const = 0;

	// Запись байтовых данных
	virtual ErrC writeBinary(const std::string& path, const std::vector<uint8_t>& data) = 0;
};

// фабричный метод для файлового обработчика
std::unique_ptr<iFiles> fileMan();
// универсальный доступ через интерфейс:
//auto fm = fileMan();   // получаем указатель на iFiles


////__________________________________________________________________________________________________

//*********************************************************
// Создаем рабочую структуру настроек по умолчанию.
//
// Если файл не существует -> записываем в файл структуру настроек по умолчанию.
//
// Если файл существует
// - читаем файл, распознаем JSON и пишем во временную структуру - все поля из файла
//
// Дальше все сравнения проводим между рабочей структурой и временной структурой из файла
//
// Сравниваем поле сигнатура - если нет или не совпадает - ошибка -> создаем структуру по умолчанию и пишем в файл.
//
// Сравниваем поле версия - если версии совпадают -> проверяем имена полей на совпаление. Если  имена полей совпали -> проверяем типы данных. Если типы данных совпали -> читаем из файла данные в рабочую структуру.
//
// Если версия программы больше версии файла:
		// сравниваем поля:
		// Если полей в файле больше - ошибка -> создаем структуру по умолчанию и пишем в файл.
		// Если полей в файле меньше -> создаем структуру по умолчанию и сверху записваем поля из файла, которые в нем есть, проверяя их типы  (в дальнейшем - будем смотреть на зависимости, если они будут)
		// пишем структуру в файл
//
// Если версия программы меньше версии файла:
		// делаем бэкап файла с указанием в имени файла версии
		// создаем структуру по умолчанию и записываем в структуру те поля из файла, которые ей соответствуют, проверяя их типы (в дальнейшем - будем смотреть на зависимости, если они будут)
		// пишем структуру в файл
//
// При несовпадении типов полей - ошибка -> создаем структуру по умолчанию и пишем в файл.
//***********************************************************


// Псевдокод обработчика чтения настроек.

// Используем: https://github.com/nlohmann/json  version 3.12.0

//def load_config(file_path, default_config) :
//	# default_config : {"signature": "...", "version" : N, ...}
//
//# 1. Файл не существует->запись default
//if not file_exists(file_path) :
//	write_json_with_retry(file_path, default_config)
//	return default_config
//
//	# 2. Чтение и парсинг
//	try :
//	raw = read_file(file_path)
//	file_config = parse_json(raw)
//	except(IOError, JSONDecodeError) :
//	backup(file_path, ".corrupted")
//	write_json_with_retry(file_path, default_config)
//	return default_config
//
//	# 3. Проверка сигнатуры(всегда)
//	if "signature" not in file_config or file_config["signature"] != default_config["signature"]:
//backup(file_path, ".bad_sig")
//write_json_with_retry(file_path, default_config)
//return default_config
//
//# 4. Проверка наличия поля version(ошибка->дефолт БЕЗ бэкапа)
//if "version" not in file_config :
//write_json_with_retry(file_path, default_config)
//return default_config
//
//file_version = file_config["version"]
//prog_version = default_config["version"]
//
//# 5. Случай равных версий
//if prog_version == file_version:
//for key, default_value in default_config.items() :
//	if key not in file_config :
//file_config[key] = default_value          # добавить отсутствующее поле
//	else :
//		if type(file_config[key]) != type(default_value) :
//			backup(file_path, ".type_mismatch")
//			write_json_with_retry(file_path, default_config)
//			return default_config
//			return file_config
//
//			# 6. Программа новее(апгрейд)
//			elif prog_version > file_version:
//result = default_config.copy()
//for key, value in file_config.items() :
//	if key in result :
//if type(value) == type(result[key]) :
//	result[key] = value
//else :
//	backup(file_path, ".type_mismatch")
//	write_json_with_retry(file_path, default_config)
//	return default_config
//	else:
//# Лишнее поле в старом файле->ошибка БЕЗ бэкапа
//write_json_with_retry(file_path, default_config)
//return default_config
//write_json_with_retry(file_path, result)
//return result
//
//# 7. Программа старше(даунгрейд)
//		else:  # prog_version < file_version
//			backup(file_path, f".v{file_version}")
//			result = default_config.copy()
//			for key in default_config.keys() :
//				if key in file_config and type(file_config[key]) == type(default_config[key]) :
//					result[key] = file_config[key]
//					elif key in file_config :
//# несовпадение типов : запись default (бэкап уже сделан)
//write_json_with_retry(file_path, default_config)
//return default_config
//write_json_with_retry(file_path, result)
//return result
//
//
//# Функция записи с повторами(3 попытки, последняя с паузой 1 сек)
//def write_json_with_retry(file_path, data, retries = 3) :
//	for attempt in range(retries) :
//		try :
//		tmp_path = file_path + ".tmp"
//		with open(tmp_path, 'w') as f :
//json.dump(data, f)
//os.replace(tmp_path, file_path)   # атомарное переименование
//return
//except(IOError, OSError) :
//	if attempt == retries - 1 :
//		raise   # последняя попытка не удалась – ошибка наверх
//		if attempt == retries - 2:        # предпоследняя попытка – пауза 1 сек
//			time.sleep(1)
//		else:
//time.sleep(0.1)
//
//
//# Функция бэкапа с уникальным именем(timestamp + суффикс)
//def backup(file_path, suffix) :
//	timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
//	backup_path = f"{file_path}.{timestamp}{suffix}"
//	# Копируем даже повреждённый файл(если read error – просто не копируем)
//	try :
//	copy_file(file_path, backup_path)
//	except :
//	pass   # не мешаем основной логике, бэкап не критичен