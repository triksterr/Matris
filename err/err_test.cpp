// @file: err_test2.cpp

#include <iostream>

#include "err.h"

// Настройка глобальных флагов (изменяем поведение вывода)
void configureErrorHandler()
{
    CallStackManager::setMaxDepth(50); // глубина стека вызовов

    // Флаги поведения
    ErrInfo::handlerEnabled = true; // включить обработку ошибок
    ErrInfo::fatalEnabled = true; // включить обработку фатальных ошибок (завершать программу или нет)
    ErrInfo::returnEnabled = true; // включить обработку ошибок с возвратом из функций (выполнять возврат или нет)
    ErrInfo::stackEnabled = true; // включить обработку стека вызовов (писать или нет)

    // Флаги фильтрации логирования
    ErrInfo::printError = true; // выводить любые ошибки (если false – тишина)
    ErrInfo::printOk = false; // не выводить ошибки с кодом ErrC::Ok
    ErrInfo::logSimpleErrors = true;
    ErrInfo::logReturnErrors = true;
    ErrInfo::logFatalErrors = true;

    // Прочие настройки
    ErrInfo::FullPrint = false; // вид сообщения об ошибках: false = краткий формат, true = подробный отчёт
    ErrInfo::LogToFile = false; // true = писать в error.log, false = в stderr
    ErrInfo::TimePrecision = 1; // точность временных меток: 0=сек, 1=мсек, 2=мксек, 3=нсек

    ErrInfo::logErrorFlag = false; // флаг ошибки лог-файла
}

// Пользовательский обработчик фатальных ошибок (опционально)
void myFatalHandler(const ErrInfo& info)
{
// Действия перед завершением: запись в системный лог, отправка метрики и т.п.
    std::cerr << "[CUSTOM FATAL] " << info.toStr();
    // Можно вызвать exit() или abort(), но лучше не возвращаться.
    // Если этот обработчик возвращает управление, ErrInfo::fatal() вызовет abort().
}

// Примеры использования err:

// Функция возвращает Error (полноценный объект с контекстом)
Error divide(double a, double b, double& result)
{
    TRACE_FUNCTION();     // обязательно в начале каждой функции, где нужен стек

    if(b == 0.0)
    {
        // Возврат ошибки с переменной (значение b преобразуем в строку)
        RETURN_ERROR(ErrC::DivisionByZero, "b", std::to_string(b), "Division by zero");
    }
    result = a / b;
    return Error();       // успех (ErrC::Ok, без печати т.к. printOk = false)
}

// Функция возвращает код ошибки (ErrC) – без создания объекта Error
ErrC processValue(int value)
{
    TRACE_FUNCTION();

    // Проверка условия с возвратом кода ошибки
    CHECK_ERROR_CODE(value > 0, ErrC::InvalidArg, "value", std::to_string(value), "Value must be positive");

    // Логирование ошибки без прерывания (продолжаем выполнение)
    if(value > 1000)
    {
        LOG_ERROR(ErrC::InvalidArg, "value", std::to_string(value), "Value is too large, will be clamped");
        value = 1000;   // корректируем и продолжаем
    }

    // Простое логирование без переменной
    LOG_ERROR_SIMPLE(ErrC::Ok, "Value processed successfully"); // не печатается из-за printOk=false

    return ErrC::Ok;
}

// Функция, которая может вызвать фатальную ошибку
void criticalOperation(int handle)
{
    TRACE_FUNCTION();

    // Если условие ложно – фатальная ошибка (программа завершится)
    CHECK_FATAL(handle != 0, ErrC::FatalError, "handle", std::to_string(handle), "Invalid handle, cannot continue");

    // Альтернативная запись: если условие ложно – сами вызываем FATAL
    if(handle < 0)
    {
        FATAL_ERROR(ErrC::FatalError, "handle", std::to_string(handle), "Negative handle, fatal");
    }
}

// Функция более высокого уровня, использующая предыдущие
Error highLevelProcess(int x, int y)
{
    TRACE_FUNCTION();

    double res;
    // CHECK_ERROR – если условие ложно, возвращаем Error
    CHECK_ERROR(x != 0, ErrC::InvalidArg, "x", std::to_string(x), "x cannot be zero");

    auto err = divide(x, y, res);
    if(err.isError())
    {
        // Добавляем свой контекст и возвращаем новую ошибку
        RETURN_ERROR_SIMPLE(ErrC::DivisionError, "Failed to divide");
    }

    // Используем функцию, возвращающую код ошибки
    ErrC code = processValue(res);
    if(code != ErrC::Ok)
    {
        RETURN_ERROR(code, "res", std::to_string(res), "processValue failed");
    }

    return Error();
}



class Calculator
{
public:
    Error divide(double a, double b, double& result)
    {
        TRACE_FUNCTION();

        if(b == 0)
        {
            RETURN_ERROR(DivisionByZero, "b", STR(b), "Division by zero");
        }

        result = a / b;
        return Error();
    }

    Error processCalculation(double x, double y, double& output)
    {
        TRACE_FUNCTION();

        double temp;
        auto err = divide(x, y, temp);
        if(err.isError())
        {
            RETURN_ERROR_SIMPLE(DivisionError, "Failed in divide operation");
        }

        output = temp * 2;
        return Error();
    }

    Error complexOperation(double a, double b, double c, double& result)
    {
        TRACE_FUNCTION();

        // Проверка с автоматическим возвратом ошибки
        CHECK_ERROR(a > 0, ArgNotPositive, "a", STR(a), "Parameter a must be positive");
        CHECK_ERROR(b != 0, ArgEqZero, "b", STR(b), "Parameter b cannot be zero");

        double temp;
        auto err = divide(a, b, temp);
        if(err.isError())
        {
            RETURN_ERROR(DivisionError, "a,b", STR(a) + "," + STR(b), "Division failed in complex operation");
        }

        result = temp * c;
        return Error();
    }
};

// Пример использования с пользовательским вводом
class FileProcessor
{
public:
    Error readValue(int& value)
    {
        TRACE_FUNCTION();

        std::cout << "Enter a positive number: ";
        std::cin >> value;

        if(value <= 0)
        {
            RETURN_ERROR(ArgNotPositive, "value", STR(value), "Value must be positive");
        }

        return Error();
    }

    Error process()
    {
        TRACE_FUNCTION();

        int input;
        auto err = readValue(input);
        if(err.isError()) {
            RETURN_ERROR(InvalidInput, "input", "invalid", "Failed to read valid input");
        }

        std::cout << "Successfully processed value: " << input << std::endl;
        return Error();
    }
};



//Ключевые возможности :
//
//Тип ошибки(код возврата) - целочисленный код в структуре ErrorInfo
//
//Имя файла - автоматически через __FILE__
//
//Номер строки - автоматически через __LINE__
//
//Имя функции - через __FUNCTION__
//
//Цепочка вызовов - через CallStackManager с макросом TRACE_FUNCTION()
//
//Значение переменной - передаётся как строка в макрос
//
//Комментарий - произвольный текст

// Простая ошибка
// MAKE_ERROR_SIMPLE(100, "Something went wrong").print();

// С переменной
// MAKE_ERROR(NotFound, "userId", "12345", "User not found").print();

// С проверкой условия
// CHECK_ERROR(x > 0, InvalidArg, "x", std::to_string(x), "Invalid x value");
// CHECK_ERROR(x > 0, ERRC(4), "x", STR(x), "Invalid x value"); // с макросами преобразования

// С возвратом из функции
// RETURN_ERROR(600, "param", param, "Invalid parameter");


int main()
{
    // Настройка глобального поведения
    configureErrorHandler();
    ErrInfo::setFatalHandler(myFatalHandler);  // установка своего обработчика фаталов


    std::cout << "Test 0: My tetsts\n";

    ERR_LS(PartImplemented, "Test 0: PartImplemented"); // сгенерированная ошибка

    std::cout << "\n---\n\n";

    // фатальная ошибка

    std::cout << "Fatal errors test\n";

    int value;
    std::cout << "Enter a positive number: ";
    std::cin >> value;

    if(value <= 0)
    {
        ERR_FS(FatalError, "HZ!"); // вылет из программы
    }

    // или так

    ERR_CFS(value > 0, FatalError, "value <= 0"); //  с проверкой внутри макроса

    std::cout << "\n---\n\n";

    // --- Демонстрация 1: обычная ошибка (не фатальная) ---
    std::cout << "Test 1: Normal error\n";
    {
        auto err = highLevelProcess(10, 0);   // деление на ноль
        if(err.isError())
        {
            err.print();       // печать ошибки (зависит от FullPrint и LogToFile)
        }
    }
    std::cout << "\n---\n\n";

    // --- Демонстрация 2: успешный вызов (печататься не будет из-за printOk=false) ---
    std::cout << "Test 2: Success: no error, printOk=false\n";
    {
        auto err = highLevelProcess(10, 2);
        if(err.isError())
        {
            err.print();
        }
        else
        {
            std::cout << "Success, no error\n";
        }
    }
    std::cout << "\n---\n\n";

    // --- Демонстрация 3: логирование без возврата ---
    std::cout << "Test 3: Logging without return\n";
    {
        int val = -5;
        // Просто логируем ошибку (не прерываем функцию)
        LOG_ERROR(ErrC::InvalidArg, "val", std::to_string(val), "Negative value, but we continue");
        std::cout << "After LOG_ERROR, still alive\n";
    }
    std::cout << "\n---\n\n";

    // --- Демонстрация 4: возврат кода ошибки ---
    // Закомментировать для выполнения дальнейших тестов
    std::cout << "Test 4: Return error code\n";
    //{
    //    int arr[] = { 1, 2, 3 };
    //    for(int i = 0; i < 5; ++i) 
    //    {
    //        // Используем CHECK_ERROR_CODE – при ошибке выходим из цикла с кодом
    //        CHECK_ERROR_CODE(i < 3, ErrC::OutOfRange, "index", std::to_string(i), "Array index out of bounds");
    //        std::cout << "arr[" << i << "] = " << arr[i] << "\n";
    //    }
    //}

    std::cout << "\n---\n\n";

    // --- Демонстрация 5: фатальная ошибка (завершит программу) ---
    std::cout << "Test 5: FATAL Function\n";
    //criticalOperation(0); //! вызовет FATAL и программа завершится (комментируем для демо)
    std::cout << "\n---\n\n";

    // Демонстрация 6: Ошибка деления на ноль
    std::cout << "Test 6: Division by zero\n";
    Calculator calc;
    double result;
    auto err = calc.processCalculation(10, 0, result);
    if(err.isError())
    {
        std::cout << "Error caught and handled!\n";
    }

    std::cout << "\n---\n\n";

    // Демонстрация 7: Ошибка ввода
    std::cout << "Test 7: Invalid input\n";
    FileProcessor processor;
    err = processor.process();
    if(err.isError())
    {
        std::cout << "Error caught!\n";
    }

    std::cout << "\n---\n\n";

    // Демонстрация 8: Комплексная операция с несколькими проверками
    std::cout << "Test 8: Complex operation with multiple checks\n";
    err = calc.complexOperation(-5, 2, 3, result);
    if(err.isError())
    {
        std::cout << "Error caught: " << err.getInfo().comment << "\n";
    }

    std::cout << "\n---\n\n";

    // Демонстрация 9: Ручное создание ошибки
    std::cout << "Test 9: Manual error creation\n";

    auto manualError = MAKE_ERROR(UserError, "test_var", "123", "");
    manualError.print();

    std::cout << "\n---\n\n";

    // Демонстрация 10: Успешная операция
    std::cout << "Test 10: Successful operation\n";

    err = calc.processCalculation(10, 2, result);
    if(!err.isError())
    {
        auto manualError = MAKE_ERROR(Ok, "", "", "");
        manualError.print();

        std::cout << "Operation successful! Result: " << result << "\n";
    }

    return 0;
}
