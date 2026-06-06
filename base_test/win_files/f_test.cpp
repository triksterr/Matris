#include <iostream>
#include "iFiles.h"

int main() {
    iFiles fm;

    // Проверка существования
    if (fm.exists("test.txt") == ErrC::SUCCESS) 
	{
        std::cout << "Файл существует\n";
    }
	else 
	{
        std::cout << "Файла нет\n";
    }

    // Запись текста
    std::string content = "Hello, Windows!";
    fm.writeText("test.txt", content);

    // Чтение текста
    std::string readContent;
    fm.readText("test.txt", readContent);
    std::cout << "Прочитано: " << readContent << std::endl;

    // Бинарные операции
    std::vector<uint8_t> binData = {0x01, 0x02, 0xFF};
    fm.writeBinary("data.bin", binData);

    std::vector<uint8_t> readBin;
    fm.readBinary("data.bin", readBin);
    // readBin == binData
}