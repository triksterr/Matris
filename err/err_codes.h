#pragma once
// @file: err.h

// Коды ошибок

enum ErrC : int
{
	Ok = 0, // ошибок нет

    NotImplemented = 1, // метод не реализован
    PartImplemented, // метод реализован не полностью

    UnknnownError, // неопределенная/неизвестная/любая ошибка
    UserError, // сгенерированная пользователем ошибка
    FatalError, // фатальная ошибка - завершение программы
    Warning, // сообщение - не ошибка

    InvalidArg, // неверный аргумент
    ArgEqZero, // аргумент = 0
    ArgNotEqZero, // аргумент не = 0
    ArgNegative, // аргумент < 0
    ArgNotNegative, // аргумент >= 0
    ArgPositive, // аргумент > 0
    ArgNotPositive, // аргумент <= 0
    ArgOutOfRange, // аргумент вне диапазона
    ArgMore, // аргумент слишком большой
    ArgLess, // аргумент слишком маленький

    NotFound, // не найдено (например, элемент в массиве)

    OutOfRange, // вне диапазона (например, за границей массива)

    InvalidState, // неверное состояние
    OutOfMemory, // ошибка выделения памяти / нехватка памяти

    // Ошибки операций
    OperationError, // ошибка операции
    DivisionByZero, // деление на 0
    DivisionError, // ошибка деления

    // 
    InvalidInput, // неверный ввод

	// файловые ошибки
    FileNotFound, // файл не найден
    FileOpenFailed, // файл не открывается
    FileReadFailed, // файл не читается
    FileWriteFailed, // ошибка записи в файл
    FileCorrupted, // файл поврежден
    FileAccessFailed, // Нет доступа к файлу (или файл заблокирован)
    NotAFile, // Путь указывает на директорию, а не на файл


    ResourceNotFound, // файл физически есть, но ресурс внутри не найден


    // JSON
    JsonParseFailed, // ошибка парсинга JSON
    JsonInvalidFormat, // неверный формат JSON
    JsonVersionUnsupp, // неподдерживаемая версия JSON

    // Изображения
    ImageDecodeFailed, // изображение не декодируется
    ImageFormatUnsupp, // формат файла изображения не поддерживается

    // Звук
    AudioDecodeFailed, // звук не декодируется
    AudioFormatUnsupp, // формат звука не поддерживается

    ErrCodesCount // общее количество кодов ошибок - не ошибка!
};

