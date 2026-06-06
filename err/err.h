#pragma once

// ============================================================================
// ќбработчик ошибок с автоматическим сбором контекста
// ¬ерси¤ 3.0 (с уровн¤ми реакции и условной компил¤цией)
// ============================================================================

/**
 * @def ERR_DISABLE_ALL
 * ѕрепроцессорный макрос. ≈сли определЄн, все макросы обработчика (кроме
 * RETURN_ERROR_CODE/CHECK_ERROR_CODE) превращаютс¤ в пустые инструкции.
 * Ёто позвол¤ет полностью убрать код обработчика из релизной сборки.
 */

#include "magic_enum.hpp"
#include "err_codes.h"
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <ctime>
#include <mutex>
#include <algorithm>

#pragma warning(disable : 4996)

// ----------------------------------------------------------------------------
// ¬спомогательный макрос STR() Ц преобразование в строку
// ----------------------------------------------------------------------------
template<class T>
std::string STR(const T& v)
{
    std::ostringstream ss;
    ss << v;
    return ss.str();
}

#define ERRC(x) static_cast<ErrC>(x)

// ----------------------------------------------------------------------------
//  ласс CallStackManager Ц управление стеком вызовов (RAII)
// ----------------------------------------------------------------------------
class CallStackManager
{
private:
    static thread_local std::vector<std::string> callStack;
    static int maxDepth;

public:
    static void push(const std::string& function, const std::string& file, int line);
    static void pop();
    static std::vector<std::string> getCallStack();
    static void clear();
    static void setMaxDepth(int depth);
};

// ----------------------------------------------------------------------------
// —труктура ErrInfo Ц информаци¤ об ошибке + статические флаги управлени¤
// ----------------------------------------------------------------------------
struct ErrInfo
{
    ErrC errCode;
    std::string errName;
    std::string fileName;
    int lineNumber;
    std::string functionName;
    std::vector<std::string> callStack;
    std::string variableName;
    std::string variableValue;
    std::string comment;
    std::string timestamp;

    // ------------------------------------------------------------------------
    // ‘лаги поведени¤ (run-time)
    // ------------------------------------------------------------------------
    static bool handlerEnabled;   // глобальный выключатель всех действий (кроме return_code)
    static bool fatalEnabled;     // если false Ц фаталы не завершают программу
    static bool returnEnabled;    // если false Ц RETURN_ERROR/CHECK_ERROR только логируют
    static bool stackEnabled;     // если false Ц TRACE_FUNCTION ничего не добавл¤ет

    // ------------------------------------------------------------------------
    // ‘лаги фильтрации логировани¤
    // ------------------------------------------------------------------------
    static bool printError;       // мастер-флаг печати (если false Ц ничего не печатать)
    static bool printOk;          // печатать ли успешные коды (ErrC::Ok)
    static bool logSimpleErrors;  // LOG_ERROR / LOG_ERROR_SIMPLE
    static bool logReturnErrors;  // RETURN_ERROR / CHECK_ERROR / RETURN_ERROR_CODE / CHECK_ERROR_CODE
    static bool logFatalErrors;   // FATAL_ERROR / CHECK_FATAL

    // ------------------------------------------------------------------------
    // ѕрочие настройки
    // ------------------------------------------------------------------------
    static bool FullPrint;        // подробный или краткий вывод
    static bool LogToFile;        // вывод в файл или в stderr
    static int TimePrecision;     // точность временной метки
    static bool logErrorFlag;     // флаг ошибки файла лога

    // ------------------------------------------------------------------------
    // ѕубличные методы
    // ------------------------------------------------------------------------
    ErrInfo();
    ~ErrInfo();

    static ErrInfo createError(ErrC code, const std::string& file, int line,
        const std::string& func, const std::string& varName,
        const std::string& varValue, const std::string& comment,
        const std::vector<std::string>& callStack);

    std::string getFilename(const std::string& path) const;
    std::string toString() const;   // полный отчЄт
    std::string toStr() const;      // краткий отчЄт
    void print() const;             // печать с учЄтом фильтров

    // ”правление логированием в файл
    static void setLogToFile(const std::string& filename);
    static void setLogToCerr();

    // ”правление фатальным обработчиком
    using FatalHandler = void(*)(const ErrInfo&);
    static void setFatalHandler(FatalHandler handler);
    static void flushLog();
    static void fatal(const ErrInfo& info);

private:
    static std::string getCurrentTimestamp();

    static std::mutex logMutex;
    static std::ostream* logStream;
    static std::ofstream fileLog;
    static FatalHandler s_fatalHandler;
};

// ----------------------------------------------------------------------------
//  ласс Error Ц обЄртка дл¤ возврата ошибки из функции
// ----------------------------------------------------------------------------
class Error
{
private:
    ErrInfo info;
    bool hasError;

public:
    Error() : hasError(false) {}
    explicit Error(const ErrInfo& info) : info(info), hasError(true) {}
    bool isError() const { return hasError; }
    const ErrInfo& getInfo() const { return info; }
    void print() const { if(hasError) info.print(); }
};

// ----------------------------------------------------------------------------
// ¬нутренние макросы (не дл¤ пр¤мого использовани¤)
// ----------------------------------------------------------------------------
#if !defined(ERR_DISABLE_ALL)

// 1. TRACE_FUNCTION запись функции в стек вызовов
#define _TRACE_FUNCTION_IMPL(file, line, func) \
    if (ErrInfo::stackEnabled) { \
        CallStackManager::push(func, file, line); \
        struct TraceGuard##line { ~TraceGuard##line() { CallStackManager::pop(); } } traceGuard##line; \
    } else { struct TraceGuard##line { ~TraceGuard##line() {} } traceGuard##line; }

// 2. —оздание ErrInfo (без возврата)
#define _MAKE_ERROR_IMPL(error_code, file, line, func, var_name, var_value, comment, stack) \
    ErrInfo::createError(error_code, file, line, func, var_name, var_value, comment, stack)

#define _MAKE_ERROR_SIMPLE_IMPL(error_code, file, line, func, comment, stack) \
    ErrInfo::createError(error_code, file, line, func, "", "", comment, stack)

// 3. Ћогирование без возврата (LOG_ERROR)
#define _LOG_ERROR_IMPL(error_code, file, line, func, var_name, var_value, comment, stack) \
    do { \
        if (ErrInfo::handlerEnabled && ErrInfo::printError && ErrInfo::logSimpleErrors) { \
            auto errInfo = ErrInfo::createError(error_code, file, line, func, var_name, var_value, comment, stack); \
            errInfo.print(); \
        } \
    } while(0)

#define _LOG_ERROR_SIMPLE_IMPL(error_code, file, line, func, comment, stack) \
    do { \
        if (ErrInfo::handlerEnabled && ErrInfo::printError && ErrInfo::logSimpleErrors) { \
            auto errInfo = ErrInfo::createError(error_code, file, line, func, "", "", comment, stack); \
            errInfo.print(); \
        } \
    } while(0)

// 4. RETURN_ERROR (возврат Error)
#define _RETURN_ERROR_IMPL(error_code, file, line, func, var_name, var_value, comment, stack) \
    do { \
        if (ErrInfo::handlerEnabled && ErrInfo::printError && ErrInfo::logReturnErrors) { \
            auto errInfo = ErrInfo::createError(error_code, file, line, func, var_name, var_value, comment, stack); \
            errInfo.print(); \
        } \
        if (ErrInfo::handlerEnabled && ErrInfo::returnEnabled) { \
            auto errInfo = ErrInfo::createError(error_code, file, line, func, var_name, var_value, comment, stack); \
            return Error(errInfo); \
        } \
    } while(0)

#define _RETURN_ERROR_SIMPLE_IMPL(error_code, file, line, func, comment, stack) \
    do { \
        if (ErrInfo::handlerEnabled && ErrInfo::printError && ErrInfo::logReturnErrors) { \
            auto errInfo = ErrInfo::createError(error_code, file, line, func, "", "", comment, stack); \
            errInfo.print(); \
        } \
        if (ErrInfo::handlerEnabled && ErrInfo::returnEnabled) { \
            auto errInfo = ErrInfo::createError(error_code, file, line, func, "", "", comment, stack); \
            return Error(errInfo); \
        } \
    } while(0)

// 5. RETURN_ERROR_CODE (возврат кода ошибки)
#define _RETURN_ERROR_CODE_IMPL(error_code, file, line, func, var_name, var_value, comment, stack) \
    do { \
        if (ErrInfo::handlerEnabled && ErrInfo::printError && ErrInfo::logReturnErrors) { \
            auto errInfo = ErrInfo::createError(error_code, file, line, func, var_name, var_value, comment, stack); \
            errInfo.print(); \
        } \
        return error_code; \
    } while(0)

#define _RETURN_ERROR_CODE_SIMPLE_IMPL(error_code, file, line, func, comment, stack) \
    do { \
        if (ErrInfo::handlerEnabled && ErrInfo::printError && ErrInfo::logReturnErrors) { \
            auto errInfo = ErrInfo::createError(error_code, file, line, func, "", "", comment, stack); \
            errInfo.print(); \
        } \
        return error_code; \
    } while(0)

// 6. CHECK_ERROR (условный RETURN_ERROR)
#define _CHECK_ERROR_IMPL(condition, error_code, file, line, func, var_name, var_value, comment, stack) \
    if (ErrInfo::handlerEnabled && !(condition)) { \
        _RETURN_ERROR_IMPL(error_code, file, line, func, var_name, var_value, comment, stack); \
    }

#define _CHECK_ERROR_SIMPLE_IMPL(condition, error_code, file, line, func, comment, stack) \
    if (ErrInfo::handlerEnabled && !(condition)) { \
        _RETURN_ERROR_SIMPLE_IMPL(error_code, file, line, func, comment, stack); \
    }

// 7. CHECK_ERROR_CODE (условный RETURN_ERROR_CODE)
#define _CHECK_ERROR_CODE_IMPL(condition, error_code, file, line, func, var_name, var_value, comment, stack) \
    if (ErrInfo::handlerEnabled && !(condition)) { \
        _RETURN_ERROR_CODE_IMPL(error_code, file, line, func, var_name, var_value, comment, stack); \
    }

#define _CHECK_ERROR_CODE_SIMPLE_IMPL(condition, error_code, file, line, func, comment, stack) \
    if (ErrInfo::handlerEnabled && !(condition)) { \
        _RETURN_ERROR_CODE_SIMPLE_IMPL(error_code, file, line, func, comment, stack); \
    }

// 8. FATAL_ERROR
#define _FATAL_ERROR_IMPL(error_code, file, line, func, var_name, var_value, comment, stack) \
    do { \
        bool shouldLog = (ErrInfo::handlerEnabled && ErrInfo::printError && ErrInfo::logFatalErrors); \
        auto errInfo = ErrInfo::createError(error_code, file, line, func, var_name, var_value, comment, stack); \
        if (shouldLog) { \
            errInfo.print(); \
        } \
        if (ErrInfo::handlerEnabled && ErrInfo::fatalEnabled) { \
            ErrInfo::fatal(errInfo); \
        } else if (ErrInfo::handlerEnabled && ErrInfo::printError && ErrInfo::logFatalErrors) { \
            /* фаталы отключены Ц только логирование уже сделано */ \
        } \
    } while(0)

#define _FATAL_ERROR_SIMPLE_IMPL(error_code, file, line, func, comment, stack) \
    do { \
        bool shouldLog = (ErrInfo::handlerEnabled && ErrInfo::printError && ErrInfo::logFatalErrors); \
        auto errInfo = ErrInfo::createError(error_code, file, line, func, "", "", comment, stack); \
        if (shouldLog) { \
            errInfo.print(); \
        } \
        if (ErrInfo::handlerEnabled && ErrInfo::fatalEnabled) { \
            ErrInfo::fatal(errInfo); \
        } \
    } while(0)

// 9. CHECK_FATAL
#define _CHECK_FATAL_IMPL(condition, error_code, file, line, func, var_name, var_value, comment, stack) \
    if (ErrInfo::handlerEnabled && !(condition)) { \
        _FATAL_ERROR_IMPL(error_code, file, line, func, var_name, var_value, comment, stack); \
    }

#define _CHECK_FATAL_SIMPLE_IMPL(condition, error_code, file, line, func, comment, stack) \
    if (ErrInfo::handlerEnabled && !(condition)) { \
        _FATAL_ERROR_SIMPLE_IMPL(error_code, file, line, func, comment, stack); \
    }

#else // defined(ERR_DISABLE_ALL)

// «аглушки дл¤ полного вырезани¤ кода (кроме RETURN_ERROR_CODE/CHECK_ERROR_CODE)
#define _TRACE_FUNCTION_IMPL(file, line, func)          do { (void)0; } while(0)
#define _MAKE_ERROR_IMPL(...)                           (ErrInfo())
#define _MAKE_ERROR_SIMPLE_IMPL(...)                    (ErrInfo())
#define _LOG_ERROR_IMPL(...)                            do { (void)0; } while(0)
#define _LOG_ERROR_SIMPLE_IMPL(...)                     do { (void)0; } while(0)
#define _RETURN_ERROR_IMPL(...)                         do { (void)0; } while(0)
#define _RETURN_ERROR_SIMPLE_IMPL(...)                  do { (void)0; } while(0)
#define _CHECK_ERROR_IMPL(condition, ...)               do { (void)0; } while(0)
#define _CHECK_ERROR_SIMPLE_IMPL(condition, ...)        do { (void)0; } while(0)
#define _CHECK_ERROR_CODE_IMPL(condition, error_code, ...) \
    if (!(condition)) return error_code;
#define _CHECK_ERROR_CODE_SIMPLE_IMPL(condition, error_code, ...) \
    if (!(condition)) return error_code;
#define _FATAL_ERROR_IMPL(...)                          do { (void)0; } while(0)
#define _FATAL_ERROR_SIMPLE_IMPL(...)                   do { (void)0; } while(0)
#define _CHECK_FATAL_IMPL(condition, ...)               do { (void)0; } while(0)
#define _CHECK_FATAL_SIMPLE_IMPL(condition, ...)        do { (void)0; } while(0)

// RETURN_ERROR_CODE Ц всегда возвращает код
#define _RETURN_ERROR_CODE_IMPL(error_code, ...)        return error_code
#define _RETURN_ERROR_CODE_SIMPLE_IMPL(error_code, ...) return error_code

#endif // !ERR_DISABLE_ALL

// ----------------------------------------------------------------------------
// ѕубличные макросы дл¤ пользовател¤
// ----------------------------------------------------------------------------

#define TRACE_FUNCTION() \
    _TRACE_FUNCTION_IMPL(__FILE__, __LINE__, __FUNCTION__)

#define MAKE_ERROR(error_code, var_name, var_value, comment) \
    _MAKE_ERROR_IMPL(error_code, __FILE__, __LINE__, __FUNCTION__, var_name, var_value, comment, CallStackManager::getCallStack())

#define MAKE_ERROR_SIMPLE(error_code, comment) \
    _MAKE_ERROR_SIMPLE_IMPL(error_code, __FILE__, __LINE__, __FUNCTION__, comment, CallStackManager::getCallStack())

#define LOG_ERROR(error_code, var_name, var_value, comment) \
    _LOG_ERROR_IMPL(error_code, __FILE__, __LINE__, __FUNCTION__, var_name, var_value, comment, CallStackManager::getCallStack())

#define LOG_ERROR_SIMPLE(error_code, comment) \
    _LOG_ERROR_SIMPLE_IMPL(error_code, __FILE__, __LINE__, __FUNCTION__, comment, CallStackManager::getCallStack())

#define RETURN_ERROR(error_code, var_name, var_value, comment) \
    _RETURN_ERROR_IMPL(error_code, __FILE__, __LINE__, __FUNCTION__, var_name, var_value, comment, CallStackManager::getCallStack())

#define RETURN_ERROR_SIMPLE(error_code, comment) \
    _RETURN_ERROR_SIMPLE_IMPL(error_code, __FILE__, __LINE__, __FUNCTION__, comment, CallStackManager::getCallStack())

#define RETURN_ERROR_CODE(error_code, var_name, var_value, comment) \
    _RETURN_ERROR_CODE_IMPL(error_code, __FILE__, __LINE__, __FUNCTION__, var_name, var_value, comment, CallStackManager::getCallStack())

#define RETURN_ERROR_CODE_SIMPLE(error_code, comment) \
    _RETURN_ERROR_CODE_SIMPLE_IMPL(error_code, __FILE__, __LINE__, __FUNCTION__, comment, CallStackManager::getCallStack())

#define CHECK_ERROR(condition, error_code, var_name, var_value, comment) \
    _CHECK_ERROR_IMPL(condition, error_code, __FILE__, __LINE__, __FUNCTION__, var_name, var_value, comment, CallStackManager::getCallStack())

#define CHECK_ERROR_SIMPLE(condition, error_code, comment) \
    _CHECK_ERROR_SIMPLE_IMPL(condition, error_code, __FILE__, __LINE__, __FUNCTION__, comment, CallStackManager::getCallStack())

#define CHECK_ERROR_CODE(condition, error_code, var_name, var_value, comment) \
    _CHECK_ERROR_CODE_IMPL(condition, error_code, __FILE__, __LINE__, __FUNCTION__, var_name, var_value, comment, CallStackManager::getCallStack())

#define CHECK_ERROR_CODE_SIMPLE(condition, error_code, comment) \
    _CHECK_ERROR_CODE_SIMPLE_IMPL(condition, error_code, __FILE__, __LINE__, __FUNCTION__, comment, CallStackManager::getCallStack())

#define FATAL_ERROR(error_code, var_name, var_value, comment) \
    _FATAL_ERROR_IMPL(error_code, __FILE__, __LINE__, __FUNCTION__, var_name, var_value, comment, CallStackManager::getCallStack())

#define FATAL_ERROR_SIMPLE(error_code, comment) \
    _FATAL_ERROR_SIMPLE_IMPL(error_code, __FILE__, __LINE__, __FUNCTION__, comment, CallStackManager::getCallStack())

#define CHECK_FATAL(condition, error_code, var_name, var_value, comment) \
    _CHECK_FATAL_IMPL(condition, error_code, __FILE__, __LINE__, __FUNCTION__, var_name, var_value, comment, CallStackManager::getCallStack())

#define CHECK_FATAL_SIMPLE(condition, error_code, comment) \
    _CHECK_FATAL_SIMPLE_IMPL(condition, error_code, __FILE__, __LINE__, __FUNCTION__, comment, CallStackManager::getCallStack())

// ----------------------------------------------------------------------------
//  раткие алиасы (опционально)
// ----------------------------------------------------------------------------
#define ERR_TF  TRACE_FUNCTION
#define ERR_M   MAKE_ERROR
#define ERR_MS  MAKE_ERROR_SIMPLE
#define ERR_LOG LOG_ERROR
#define ERR_LS  LOG_ERROR_SIMPLE
#define ERR_RET RETURN_ERROR
#define ERR_RS  RETURN_ERROR_SIMPLE
#define ERR_RETC RETURN_ERROR_CODE
#define ERR_RSC  RETURN_ERROR_CODE_SIMPLE
#define ERR_C   CHECK_ERROR
#define ERR_CS  CHECK_ERROR_SIMPLE
#define ERR_CC  CHECK_ERROR_CODE
#define ERR_CSC CHECK_ERROR_CODE_SIMPLE
#define ERR_FATAL   FATAL_ERROR
#define ERR_FS      FATAL_ERROR_SIMPLE
#define ERR_CF      CHECK_FATAL
#define ERR_CFS     CHECK_FATAL_SIMPLE