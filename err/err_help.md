## Полная документация 

# Обработчик ошибок с автоматическим сбором контекста

Версия 3.0 – с уровнями реакции, гибкой фильтрацией и условной компиляцией.

## Оглавление

1. [Обзор](#обзор)
2. [Быстрый старт](#быстрый-старт)
3. [Архитектура](#архитектура)
4. [Макросы](#макросы)
5. [Управление поведением (run-time флаги)](#управление-поведением-run-time-флаги)
   - [Флаги поведения](#флаги-поведения)
   - [Флаги фильтрации логирования](#флаги-фильтрации-логирования)
6. [Условная компиляция (полное удаление кода)](#условная-компиляция-полное-удаление-кода)
7. [Настройка вывода](#настройка-вывода)
8. [Примеры использования](#примеры-использования)
9. [Совместимость и требования](#совместимость-и-требования)

---

## Обзор

Библиотека предоставляет макросы для единообразной обработки ошибок в C++ с автоматическим захватом:

- имени файла, строки, функции;
- стека вызовов (если используется `TRACE_FUNCTION`);
- значений переменных;
- временной метки.

Поддерживаются три режима реакции:

- **Логирование** – запись в `stderr` или файл без прерывания выполнения.
- **Возврат ошибки** – возврат объекта `Error` или кода ошибки (`ErrC`).
- **Фатальная ошибка** – аварийное завершение программы с возможностью пользовательского обработчика.

Все действия можно гибко включать/отключать через run-time флаги. Для release-сборки предусмотрена полная вырезка кода макросов через `ERR_DISABLE_ALL`.

---

## Быстрый старт

```cpp
#include "err.h"

Error myFunction(int x) {
    TRACE_FUNCTION();

    CHECK_ERROR(x > 0, ErrC::InvalidArgument, "x", std::to_string(x),
                "x must be positive");

    if (x == 42) {
        LOG_ERROR(ErrC::Warning, "x", std::to_string(x),
                  "The answer, but not an error");
    }

    return Error();
}

int main() {
    // Настройка (опционально)
    ErrInfo::printError = true;
    ErrInfo::FullPrint  = false;   // краткий вывод
    ErrInfo::LogToFile  = false;   // вывод в stderr

    auto err = myFunction(-5);
    if (err.isError()) err.print();
    return 0;
}
```

---

## Архитектура

- **`ErrInfo`** – структура, хранящая всю информацию об ошибке (код, имя, файл, строка, стек, переменная, комментарий, временная метка). Содержит статические флаги управления.
- **`Error`** – класс-обёртка для возврата `ErrInfo` из функций.
- **`CallStackManager`** – RAII-менеджер стека вызовов (используется макросом `TRACE_FUNCTION`).
- **Макросы** – основной интерфейс для пользователя (см. таблицу ниже).

---

## Макросы

| Макрос | Описание | Категория |
|--------|----------|-----------|
| `TRACE_FUNCTION()` | Добавляет текущую функцию в стек вызовов (RAII). | – |
| `LOG_ERROR(code, var_name, var_value, comment)` | Логирует ошибку без возврата. | простая |
| `LOG_ERROR_SIMPLE(code, comment)` | То же без переменной. | простая |
| `RETURN_ERROR(code, var_name, var_value, comment)` | Логирует и возвращает `Error`. | возврат |
| `RETURN_ERROR_SIMPLE(code, comment)` | То же без переменной. | возврат |
| `CHECK_ERROR(cond, code, var_name, var_value, comment)` | Если `cond` ложно – `RETURN_ERROR`. | возврат |
| `CHECK_ERROR_SIMPLE(cond, code, comment)` | То же без переменной. | возврат |
| `RETURN_ERROR_CODE(code, var_name, var_value, comment)` | Логирует и возвращает `code` (тип `ErrC`). | возврат (код) |
| `RETURN_ERROR_CODE_SIMPLE(code, comment)` | То же без переменной. | возврат (код) |
| `CHECK_ERROR_CODE(cond, code, var_name, var_value, comment)` | Если `cond` ложно – `RETURN_ERROR_CODE`. | возврат (код) |
| `CHECK_ERROR_CODE_SIMPLE(cond, code, comment)` | То же без переменной. | возврат (код) |
| `FATAL_ERROR(code, var_name, var_value, comment)` | Логирует и завершает программу (если включено). | фатальная |
| `FATAL_ERROR_SIMPLE(code, comment)` | То же без переменной. | фатальная |
| `CHECK_FATAL(cond, code, var_name, var_value, comment)` | Если `cond` ложно – `FATAL_ERROR`. | фатальная |
| `CHECK_FATAL_SIMPLE(cond, code, comment)` | То же без переменной. | фатальная |

> **Примечание**: макросы `RETURN_ERROR_CODE` и `CHECK_ERROR_CODE` **всегда** возвращают переданный код, даже если `handlerEnabled == false` (но логирование при этом отключается). Это гарантирует, что функция, возвращающая `ErrC`, всегда сможет вернуть значение.

---

## Управление поведением (run-time флаги)

Все флаги – статические члены `ErrInfo`. Их можно изменять в любой момент выполнения.

### Флаги поведения

| Флаг | Тип | По умолчанию | Описание |
|------|-----|--------------|-----------|
| `ErrInfo::handlerEnabled` | `bool` | `true` | Глобальный выключатель. Если `false`, все макросы (кроме `TRACE_FUNCTION` и `RETURN_ERROR_CODE`/`CHECK_ERROR_CODE`) ничего не делают; условия в `CHECK_*` **не вычисляются**. |
| `ErrInfo::fatalEnabled` | `bool` | `true` | Если `false`, фатальные макросы **не завершают программу**, а превращаются в `LOG_ERROR` (только логирование). |
| `ErrInfo::returnEnabled` | `bool` | `true` | Если `false`, то `RETURN_ERROR` и `CHECK_ERROR` **не возвращают** `Error`, а только логируют (как `LOG_ERROR`). Не влияет на `RETURN_ERROR_CODE`. |
| `ErrInfo::stackEnabled` | `bool` | `true` | Если `false`, `TRACE_FUNCTION` не добавляет информацию в стек вызовов. |

### Флаги фильтрации логирования

Все эти флаги работают **только если** `ErrInfo::printError == true`.

| Флаг | Тип | По умолчанию | Описание |
|------|-----|--------------|-----------|
| `ErrInfo::printError` | `bool` | `true` | Мастер-флаг: если `false`, ничего не печатается (даже фаталы). |
| `ErrInfo::printOk` | `bool` | `false` | Печатать ли ошибки с кодом `ErrC::Ok`. |
| `ErrInfo::logSimpleErrors` | `bool` | `true` | Печатать ли «простые» ошибки (`LOG_ERROR`, `LOG_ERROR_SIMPLE`). |
| `ErrInfo::logReturnErrors` | `bool` | `true` | Печатать ли ошибки с возвратом (`RETURN_ERROR`, `CHECK_ERROR`, `RETURN_ERROR_CODE`, `CHECK_ERROR_CODE`). |
| `ErrInfo::logFatalErrors` | `bool` | `true` | Печатать ли фатальные ошибки (`FATAL_ERROR`, `CHECK_FATAL`). |

> **Важно**: категория ошибки определяется **типом макроса**, а не значением `errCode`. Например, `LOG_ERROR(ErrC::FatalError, ...)` считается «простой» и управляется флагом `logSimpleErrors`.

---

## Условная компиляция (полное удаление кода обработчика)

Определите макрос `ERR_DISABLE_ALL` на этапе компиляции (например, через `-DERR_DISABLE_ALL` в GCC/Clang или `/DERR_DISABLE_ALL` в MSVC), чтобы:

- все макросы, кроме `RETURN_ERROR_CODE` и `CHECK_ERROR_CODE`, стали пустыми (`(void)0`);
- `RETURN_ERROR_CODE` превратился в `return error_code;`;
- `CHECK_ERROR_CODE` превратился в `if (!(condition)) return error_code;`;
- стек вызовов не собирался;
- логирование полностью исчезло.

Это позволяет включать обработчик только в отладочных сборках, а в релизе оставлять минимальную передачу кодов ошибок.

Пример сборки:

```bash
g++ -DERR_DISABLE_ALL -O2 -DNDEBUG main.cpp -o app
```

---

## Настройка вывода

- **`ErrInfo::FullPrint`** – `true`: печатать подробный отчёт (со стеком и полными путями), `false`: краткий (только время, код, имя файла, строка, функция, переменная, комментарий).
- **`ErrInfo::LogToFile`** – `true`: писать в файл `error.log` (открывается в режиме append), `false`: в `std::cerr`. Можно также вручную вызвать `ErrInfo::setLogToFile("my.log")`.
- **`ErrInfo::TimePrecision`** – 0 = секунды, 1 = миллисекунды (по умолчанию), 2 = микросекунды, 3 = наносекунды.

Пример настройки:

```cpp
ErrInfo::printError = true;
ErrInfo::FullPrint = false;
ErrInfo::LogToFile = true;
ErrInfo::TimePrecision = 2;   // микросекунды
ErrInfo::setLogToFile("myapp_errors.log");
```

---

## Примеры использования

### 1. Логирование без остановки

```cpp
void process(int value) {
    TRACE_FUNCTION();
    if (value < 0) {
        LOG_ERROR(ErrC::InvalidArgument, "value", std::to_string(value),
                  "Negative value, will be set to 0");
        value = 0;
    }
    // продолжаем работу
}
```

### 2. Возврат ошибки с полным контекстом

```cpp
Error loadConfig(const std::string& path) {
    TRACE_FUNCTION();
    std::ifstream f(path);
    CHECK_ERROR(f.is_open(), ErrC::FileNotFound, "path", path,
                "Cannot open config file");
    // ...
    return Error();
}
```

### 3. Функция, возвращающая код ошибки

```cpp
ErrC parseInt(const std::string& s, int& out) {
    TRACE_FUNCTION();
    CHECK_ERROR_CODE(!s.empty(), ErrC::InvalidArgument, "s", s,
                     "Empty string");
    // ...
    return ErrC::Ok;
}
```

### 4. Фатальная ошибка (завершение программы)

```cpp
void criticalInit() {
    TRACE_FUNCTION();
    CHECK_FATAL(global_handle != nullptr, ErrC::InitFailed,
                "global_handle", "nullptr",
                "Initialization failed, cannot continue");
}
```

### 5. Пользовательский обработчик фатальных ошибок

```cpp
void myFatalHandler(const ErrInfo& info) {
    // Дополнительные действия: запись в системный лог, отправка уведомления
    std::cerr << "CUSTOM FATAL: " << info.toStr();
    // Обработчик должен завершить программу; если вернётся – будет вызван abort()
}

int main() {
    ErrInfo::setFatalHandler(myFatalHandler);
    // ...
}
```

### 6. Полное отключение обработчика для тестирования

```cpp
void testNoHandler() {
    ErrInfo::handlerEnabled = false;
    // Теперь CHECK_ERROR ничего не делает (условие не вычисляется)
    CHECK_ERROR(1 == 0, ErrC::LogicError, "", "", "Should not happen");
    // Функция продолжит работу
}
```

---

## Совместимость и требования

- C++11 или новее (используются `std::chrono`, `std::mutex`, `std::thread_local`).
- Заголовок `magic_enum.hpp` (для преобразования перечислений в строки). Можно заменить на собственную реализацию.
- `err_codes.h` должен содержать перечисление `enum class ErrC { Ok = 0, ... };`.

Для C++20 можно добавить поддержку `std::source_location`, но в текущей версии используется классический `__FILE__`, `__LINE__`, `__FUNCTION__` (или `__func__`).

---

## Заключение

Обработчик ошибок предоставляет гибкий механизм для логирования, возврата и аварийного завершения с богатым контекстом. Настройка поведения и фильтрация позволяют адаптировать его под любые стадии разработки и эксплуатации.

Любые вопросы и предложения направляйте автору.


---

## 2. Краткая документация в виде кода с комментариями

Файл `err_quick_demo.cpp` (можно включить в проект как пример):

```cpp
// ============================================================================
// Краткая документация обработчика ошибок (err.h) – примеры всех макросов и настроек
// Версия 2.0
// ============================================================================

#include "err.h"
#include "err_codes.h"   // должно содержать enum class ErrC { Ok, InvalidArgument, FileNotFound, ... }
#include <iostream>
#include <fstream>

// ----------------------------------------------------------------------------
// 1. Настройка глобальных флагов (поместить в main или в начало потока)
// ----------------------------------------------------------------------------
void configureErrorHandler() {
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
```
