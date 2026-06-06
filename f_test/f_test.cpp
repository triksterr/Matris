#include <iostream>
#include "..\base_test\interface\i_files.h"


struct testStr 
{
	std::string name;
	std::string surname;
    int level;
	int age;

    // оператор сравнения
	bool operator==(const testStr& other) const 
    {
		return name == other.name && surname == other.surname && level == other.level && age == other.age;
	}
};
//NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(main::testStr, name, surname, level, age);
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(testStr, name, surname, level, age);

int main() 
{
    //универсальный доступ через интерфейс
    auto fm = fileMan();   // получаем указатель на iFiles

    // Надо проверять JSON

    testStr settings; //struct test settings
    settings.name = "Alex";
	settings.surname = "Smith";
	settings.level = 10;
	settings.age = 20;

    // запись JSON
    ErrC err = fm->writeJSON("settings.json", settings);
	if(err != ErrC::Ok)
        std::cout << "JSON Write Error: " << err << "\n";

    testStr settings2;

    // проверка существования
    if(fm->exists("settings.json") != ErrC::Ok)
        std::cout << "JSON File not exists\n"; // return ErrC::FileNotFound;

    // чтение JSON в структуру настроек
    err = fm->readJSON("settings.json", settings2);
    if(err != ErrC::Ok)
        std::cout << "JSON Read Error: " << err << "\n";

    if(settings == settings2)
		std::cout << "JSON Match\n";
	else
		std::cout << "JSON Mismatch\n";


    // Тесты пройдены!
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

}