#include <iostream>
#include "..\base_test\interface\i_files.h"

//#include "w_files.h"

int main() 
{
    //универсальный доступ через интерфейс
    auto fm = fileMan();   // получаем указатель на iFiles

    // Надо проверять JSON

    struct test 
    {
		std::string name;
		std::string surname;
        int level;
		int age;
	};


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
    std::cout << "Read content: " << readContent << std::endl;

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