// @file: w_files.cpp

#include "w_files.h"

// Ссылка на файловый обработчик уровня OS
// Создание экземпляра менеджера файлов для Windows
std::unique_ptr<iFiles> fileMan() // Фабрика создаёт wFiles, возвращает как iFiles
{
    return std::make_unique<wFiles>();
}
