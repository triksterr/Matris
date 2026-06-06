// @file: w_files.cpp

#include "w_files.h"

// —сылка на файловый обработчик уровн€ OS
std::unique_ptr<iFiles> fileMan() // ‘абрика создаЄт wFiles, возвращает как iFiles
{
    return std::make_unique<wFiles>();
}
