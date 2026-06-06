// ============================================================================
// Краткая документация обработчика ошибок (err.h) – примеры всех макросов и настроек
// Версия 2.0
// ============================================================================

#include "err.h"
#include "err_codes.h"   // содержит коды ошибок enum ErrC
#include <iostream>
#include <fstream>

// ----------------------------------------------------------------------------
// 1. Настройка глобальных флагов (поместить в main или в начало потока)
// ----------------------------------------------------------------------------
void configureErrorHandler() 
{
    // ===== Флаги поведения =====
    ErrInfo::handlerEnabled = true;   // полное включение обработчика
    ErrInfo::fatalEnabled   = true;   // фатальные ошибки завершают программу
    ErrInfo::returnEnabled  = true;   // RETURN_ERROR / CHECK_ERROR возвращают управление
    ErrInfo::stackEnabled   = true;   // собирать стек вызовов (TRACE_FUNCTION)

    // ===== Флаги фильтрации логирования =====
    ErrInfo::printError        = true;   // мастер-флаг печати
    ErrInfo::printOk           = false;  // не печатать успешные коды (ErrC::Ok)
    ErrInfo::logSimpleErrors   = true;   // печатать LOG_ERROR
    ErrInfo::logReturnErrors   = true;   // печатать RETURN_ERROR, CHECK_ERROR, RETURN_ERROR_CODE
    ErrInfo::logFatalErrors    = true;   // печатать FATAL_ERROR, CHECK_FATAL

    // ===== Настройки вывода =====
    ErrInfo::FullPrint      = false;     // false = краткий формат, true = подробный отчёт
    ErrInfo::LogToFile      = false;     // false = вывод в stderr, true = в error.log
    ErrInfo::TimePrecision  = 1;         // 0=сек, 1=мсек, 2=мксек, 3=нсек

    // Для вывода в файл можно также вызвать:
    // ErrInfo::setLogToFile("my_errors.log");
}

// ----------------------------------------------------------------------------
// 2. Пользовательский обработчик фатальных ошибок (опционально)
// ----------------------------------------------------------------------------
void myFatalHandler(const ErrInfo& info) {
    std::cerr << "!!! CUSTOM FATAL HANDLER !!!\n";
    std::cerr << info.toStr();   // краткий вывод
    // Здесь можно сделать core dump, запись в системный лог и т.д.
    // Функция должна завершить программу; если вернётся – ErrInfo::fatal() вызовет abort().
    std::exit(EXIT_FAILURE);
}

// ----------------------------------------------------------------------------
// 3. Функции-примеры, демонстрирующие разные макросы
// ----------------------------------------------------------------------------

// 3.1. Функция, возвращающая Error
Error divide(double a, double b, double& result) {
    TRACE_FUNCTION();      // обязательный макрос для захвата стека

    if (b == 0.0) {
        RETURN_ERROR(ErrC::ArithmeticError, "b", std::to_string(b),
                     "Division by zero");
    }
    result = a / b;
    return Error();        // успех (ErrC::Ok)
}

// 3.2. Функция, возвращающая код ошибки (ErrC)
ErrC processValue(int value) {
    TRACE_FUNCTION();

    // Если условие ложно – возвращаем код ошибки (с логированием)
    CHECK_ERROR_CODE(value > 0, ErrC::InvalidArgument,
                     "value", std::to_string(value),
                     "Value must be positive");

    // Логирование без возврата (продолжаем выполнение)
    if (value > 1000) {
        LOG_ERROR(ErrC::InvalidArgument, "value", std::to_string(value),
                  "Value too large, clamping to 1000");
        value = 1000;
    }

    return ErrC::Ok;
}

// 3.3. Функция, которая может завершиться фатально
void criticalOperation(int handle) {
    TRACE_FUNCTION();

    // Фатальная проверка
    CHECK_FATAL(handle != 0, ErrC::FatalError,
                "handle", std::to_string(handle),
                "Zero handle, cannot continue");

    // Альтернативный способ:
    if (handle < 0) {
        FATAL_ERROR_SIMPLE(ErrC::FatalError, "Negative handle");
    }
}

// ----------------------------------------------------------------------------
// 4. Пример высокоуровневой функции, объединяющей вызовы
// ----------------------------------------------------------------------------
Error highLevelProcess(int x, int y) {
    TRACE_FUNCTION();

    // Проверка аргумента с автоматическим возвратом Error
    CHECK_ERROR(x != 0, ErrC::InvalidArgument,
                "x", std::to_string(x), "x cannot be zero");

    double res;
    auto err = divide(x, y, res);
    if (err.isError()) {
        // Добавляем контекст и возвращаем новую ошибку
        RETURN_ERROR_SIMPLE(ErrC::ArithmeticError, "Divide failed");
    }

    ErrC code = processValue(static_cast<int>(res));
    if (code != ErrC::Ok) {
        RETURN_ERROR(code, "res", std::to_string(res),
                     "processValue failed");
    }

    std::cout << "Result: " << res << std::endl;
    return Error();
}

// ----------------------------------------------------------------------------
// 5. Демонстрация работы флагов (изменение поведения на лету)
// ----------------------------------------------------------------------------
void demoFlags() {
    std::cout << "\n=== Demo: disabling return (returnEnabled = false) ===\n";
    ErrInfo::returnEnabled = false;

    // Этот макрос только залогирует, но НЕ вернёт управление из функции
    // (в данном случае из demoFlags, потому что мы внутри неё)
    RETURN_ERROR(ErrC::LogicError, "test", "123", "Return disabled");

    std::cout << "Still alive after RETURN_ERROR!" << std::endl;

    // Возвращаем флаг обратно
    ErrInfo::returnEnabled = true;
}

// ----------------------------------------------------------------------------
// 6. Главная функция – демонстрация всех режимов
// ----------------------------------------------------------------------------
int main() {
    // Настройка обработчика
    configureErrorHandler();
    ErrInfo::setFatalHandler(myFatalHandler);   // комментировать, чтобы оставить стандартный abort()

    std::cout << "=== 1. Normal error (non-fatal) ===\n";
    auto err = highLevelProcess(10, 0);   // деление на ноль
    if (err.isError()) err.print();

    std::cout << "\n=== 2. Success (no print because printOk=false) ===\n";
    err = highLevelProcess(10, 2);
    if (!err.isError()) std::cout << "Success, no error\n";

    std::cout << "\n=== 3. LOG_ERROR without return ===\n";
    int val = -5;
    LOG_ERROR(ErrC::InvalidArgument, "val", std::to_string(val), "Negative but continue");
    std::cout << "After LOG_ERROR, program continues\n";

    std::cout << "\n=== 4. RETURN_ERROR_CODE demo ===\n";
    int arr[] = {1, 2, 3};
    for (int i = 0; i < 5; ++i) {
        CHECK_ERROR_CODE(i < 3, ErrC::OutOfRange,
                         "index", std::to_string(i),
                         "Array index out of bounds");
        std::cout << "arr[" << i << "] = " << arr[i] << "\n";
    }

    std::cout << "\n=== 5. Disabling return (returnEnabled = false) ===\n";
    demoFlags();

    std::cout << "\n=== 6. Fatal error (will terminate program) ===\n";
    // Раскомментировать, чтобы увидеть завершение программы:
    // criticalOperation(0);

    std::cout << "\n=== End of demo (no fatal) ===\n";
    return 0;
}

// ============================================================================
// КОММЕНТАРИИ ПО ИСПОЛЬЗОВАНИЮ:
//
// - Всегда вызывайте TRACE_FUNCTION() в начале каждой функции, где нужен стек.
// - Для преобразования переменной в строку используйте std::to_string() или STR().
// - Флаги поведения и фильтрации можно менять в любой момент, даже внутри функций.
// - При определении макроса ERR_DISABLE_ALL все макросы, кроме RETURN_ERROR_CODE
//   и CHECK_ERROR_CODE, удаляются из кода (пустые инструкции).
// - Фатальные ошибки при fatalEnabled = false превращаются в LOG_ERROR (без завершения).
// - Категория ошибки определяется макросом, а не кодом ErrC.
// ============================================================================