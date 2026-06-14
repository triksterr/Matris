#include <iostream>
#include "..\base_test\interface\i_files.h"


struct testStr 
{
    std::string name = {};
	std::string surname = {};
    int level = {};
	int age = {};

    // оператор сравнения - по полям
	//bool operator==(const testStr& other) const 
    //{
	//	return name == other.name && surname == other.surname && level == other.level && age == other.age;
	//}
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(testStr, name, surname, level, age);

// оператор сравнения структур через JSON
 // уже определили to_json / from_json (NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE()), -> можно сравнить через nlohmann::json:
bool operator==(const testStr& a, const testStr& b)
{
    return nlohmann::json(a) == nlohmann::json(b);
}


int main() 
{
    //универсальный доступ через интерфейс
    auto fm = fileMan();   // получаем указатель на iFiles

    // Операции верхнего уровня


    // --- Проверяем JSON - Тесты пройдены!

    // заполняем структуру
    testStr settings;
    settings.name = "Alex";
	settings.surname = "Smith";
	settings.level = 10;
	settings.age = 20;

    // запись JSON
    std::cout << "--- JSON Write Test ---\n";
    ErrC err = fm->writeJSON("settings.json", settings);
	if(err != ErrC::Ok)
        std::cout << "JSON Write Error: " << err << "\n";

    testStr settings2;

    // проверка существования
    if(fm->exists("settings.json") != ErrC::Ok)
        std::cout << "JSON File not exists\n";

    // чтение JSON в структуру2
	std::cout << "--- JSON Read Test ---\n";
    err = fm->readJSON("settings.json", settings2);
    if(err != ErrC::Ok)
        std::cout << "JSON Read Error: " << err << "\n";

	// сравнение
    std::cout << "--- JSON Compare Test ---\n";
    if(settings == settings2)
		std::cout << "JSON Match\n";
	else
		std::cout << "JSON Mismatch\n";

    //! --- Проверяем ошибки чтения JSON
     
    // У нас есть версия!
    // И нужно поле с сигнатурой - идентификация, что файл именно наш.

    // 1. проверка существования
	// 2. проверка сигнатуры
    // 3. проверка версии 
    
    // если хоть одно поле в файле пропало + старая версия - сначала структуру заполнить дефолтами, а потом считать все поля из файла
    // если изменился тип данных? - ошибка
    // если поля в файле добавились - новая версия - считать все поля и записать в структуру только подходящие
    // если и пропало и появилось новое - ошибка

    // Если полей в файле меньше - заполнять пустые поля дефолтными(для программы) значениями:
    //  - создаем структуру
    //  - заполняем игровыми дефолтами
    //  - переpаполняем из файла те поля, которые в нем есть

    //    Если поля добавились - новая версия
    //    Удалились - старая версия
    //    Изменили тип - ошибка
    //!    Исходную структуру с первой версии - только дополняем!

    //    Как получить имена полей структуры в виде текстовых переменных ?

    // чтение избыточного JSON (в файле больше полей) - более новая версия - но надо как-то читать все поля?
    std::cout << "--- JSON Overflow Test (more fields) ---\n";
    if(fm->exists("settings1.json") != ErrC::Ok)
        std::cout << "JSON 1 File not exists\n";
    else
    {
        err = fm->readJSON("settings1.json", settings2); // - ошибки нет, но надо как-то читать ВСЕ поля
        if(err != ErrC::Ok)
            std::cout << "JSON 1 Read Error: " << err << "\n";
    }

    // в файле что-то пропало, новое появилось - ошибка!
	std::cout << "--- JSON Overflow Test (new field) ---\n";
	if(fm->exists("settings2.json") != ErrC::Ok)
		std::cout << "JSON 2 File not exists\n";
    else
    {
        err = fm->readJSON("settings2.json", settings2); // ошибка
        if(err != ErrC::Ok)
            std::cout << "JSON 2 Read Error: " << err << "\n";
    }

    // чтение недостаточного JSON (меньше полей) - старая версия - надо как-то считать то, что есть?
	std::cout << "--- JSON Underflow Test (less fields) ---\n";
	if(fm->exists("settings3.json") != ErrC::Ok)
		std::cout << "JSON 3 File not exists\n";
    else
    {
        err = fm->readJSON("settings3.json", settings2); // ошибка
        if(err != ErrC::Ok)
            std::cout << "JSON 3 Read Error: " << err << "\n";
    }

    // чтение не с теми полями (другие названия полей) - ошибка!
	std::cout << "--- JSON Overflow Test (wrong fields names) ---\n";
	if(fm->exists("settings4.json") != ErrC::Ok)
		std::cout << "JSON 4 File not exists\n";
    else
    {
        err = fm->readJSON("settings4.json", settings2); // ошибка
        if(err != ErrC::Ok)
            std::cout << "JSON 4 Read Error: " << err << "\n";
    }

    // чтение не с теми полями (другие типы данных полей) - ошибка!
	std::cout << "--- JSON Overflow Test (wrong fields types) ---\n";
	if(fm->exists("settings5.json") != ErrC::Ok)
		std::cout << "JSON 5 File not exists\n";
    else
    {
        err = fm->readJSON("settings5.json", settings2); // ошибка
        if(err != ErrC::Ok)
            std::cout << "JSON 5 Read Error: " << err << "\n";
    }


    // --- Файловые операции - Тесты пройдены!
    
    // Проверка существования
    if (fm->exists("test.txt") == ErrC::Ok) 
        std::cout << "File exists\n";
	else 
        std::cout << "File not exists\n";

    // Запись текста
    std::string content = "Hello, Windows!";
    fm->writeText("test.txt", content);

    // Чтение текста
    std::string readContent;
    fm->readText("test.txt", readContent);
    std::cout << "Read content: " << readContent << "\n";

    // Бинарные операции
    std::vector<uint8_t> binData = {0x01, 0x02, 0xFF};
    fm->writeBinary("data.bin", binData);

    std::vector<uint8_t> readBin;
    fm->readBinary("data.bin", readBin);

    if(readBin == binData)
        std::cout << "Binary Ok\n";
    else
        std::cout << "Binary Error\n";



    return 0;
}