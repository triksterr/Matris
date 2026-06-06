#pragma once
// @file: err_codes.h


enum class ErrC {
    SUCCESS = 0,            // Операция выполнена успешно
    FILE_NOT_FOUND,         // Файл не существует
    PERMISSION_DENIED,      // Нет доступа к файлу (или файл заблокирован)
    NOT_A_FILE,             // Путь указывает на директорию, а не на файл
    READ_ERROR,             // Ошибка чтения
    WRITE_ERROR,            // Ошибка записи
    UNKNOWN_ERROR           // Прочая ошибка (например, сбой файловой системы)
};