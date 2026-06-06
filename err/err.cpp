#include "err.h"

// ============================================================================
// Определения статических членов
// ============================================================================

// Флаги поведения
bool ErrInfo::handlerEnabled = true;
bool ErrInfo::fatalEnabled = true;
bool ErrInfo::returnEnabled = true;
bool ErrInfo::stackEnabled = true;

// Флаги фильтрации логирования
bool ErrInfo::printError = true;
bool ErrInfo::printOk = false;
bool ErrInfo::logSimpleErrors = true;
bool ErrInfo::logReturnErrors = true;
bool ErrInfo::logFatalErrors = true;

// Прочие настройки
bool ErrInfo::FullPrint = false;
bool ErrInfo::LogToFile = false;
int  ErrInfo::TimePrecision = 1;
bool ErrInfo::logErrorFlag = false;

// CallStackManager
int CallStackManager::maxDepth = 100;
thread_local std::vector<std::string> CallStackManager::callStack;

// Логирование
std::ostream* ErrInfo::logStream = &std::cerr;
std::ofstream ErrInfo::fileLog;
std::mutex ErrInfo::logMutex;

// Фатальный обработчик
ErrInfo::FatalHandler ErrInfo::s_fatalHandler = nullptr;

// ============================================================================
// Реализация методов CallStackManager
// ============================================================================
void CallStackManager::push(const std::string& function, const std::string& file, int line)
{
    if(callStack.size() >= maxDepth) return;
    std::ostringstream oss;
    oss << function << " [" << file << ":" << line << "]";
    callStack.push_back(oss.str());
}

void CallStackManager::pop()
{
    if(!callStack.empty())
        callStack.pop_back();
}

std::vector<std::string> CallStackManager::getCallStack()
{
    return callStack;
}

void CallStackManager::clear()
{
    callStack.clear();
}

void CallStackManager::setMaxDepth(int depth)
{
    maxDepth = depth;
}

// ============================================================================
// Реализация ErrInfo
// ============================================================================
ErrInfo::ErrInfo() : errCode(ErrC::Ok), lineNumber(0)
{
    if(LogToFile)
        setLogToFile("error.log");

    if(TimePrecision < 0 || TimePrecision > 3)
        TimePrecision = 1;

    if(TimePrecision == 0)
    {
        auto now = std::time(nullptr);
        timestamp = std::ctime(&now);
        timestamp.pop_back();
    }
    else
    {
        timestamp = getCurrentTimestamp();
    }
}

ErrInfo::~ErrInfo()
{
    setLogToCerr();
}

ErrInfo ErrInfo::createError(ErrC code, const std::string& file, int line,
    const std::string& func, const std::string& varName,
    const std::string& varValue, const std::string& comment,
    const std::vector<std::string>& callStack)
{
    ErrInfo info;
    info.errName = magic_enum::enum_name(code);
    info.errCode = code;
    info.fileName = file;
    info.lineNumber = line;
    info.functionName = func;
    info.variableName = varName;
    info.variableValue = varValue;
    info.comment = comment;
    info.callStack = callStack;
    return info;
}

std::string ErrInfo::getFilename(const std::string& path) const
{
    size_t pos = path.find_last_of("/\\");
    if(pos == std::string::npos)
        return path;
    while(pos > 0 && (path[pos - 1] == '/' || path[pos - 1] == '\\'))
        --pos;
    return path.substr(pos + 1);
}

std::string ErrInfo::toString() const
{
    std::ostringstream oss;
    oss << "\n========== ERROR REPORT ==========\n";
    oss << "Time: " << timestamp << "\n";
    oss << "Error: " << errName << " [" << int(errCode) << "]\n";
    oss << "File: " << fileName << "\n";
    oss << "Line: " << lineNumber << "\n";
    oss << "Function: " << functionName << "\n";
    if(!variableName.empty())
        oss << "Variable: " << variableName << " = " << variableValue << "\n";
    if(!comment.empty())
        oss << "Comment: " << comment << "\n";
    if(!callStack.empty())
    {
        oss << "Call Stack:\n";
        for(size_t i = 0; i < callStack.size(); ++i)
            oss << "  " << i << ": " << callStack[i] << "\n";
    }
    oss << "===================================\n";
    return oss.str();
}

std::string ErrInfo::toStr() const
{
    std::ostringstream oss;
    oss << timestamp << " ";
    oss << "Error: " << errName << " [" << int(errCode) << "] | ";
    oss << "F " << getFilename(fileName) << " | ";
    oss << "L " << lineNumber << " | ";
    oss << "Func " << functionName;
    if(!variableName.empty())
        oss << " | Var " << variableName << " = " << variableValue;
    if(!comment.empty())
        oss << " | Comment: " << comment;
    oss << "\n";
    return oss.str();
}

void ErrInfo::print() const
{
    if(!printError)
        return;
    if(errCode == ErrC::Ok && !printOk)
        return;

    // Определяем категорию ошибки и проверяем соответствующий флаг фильтрации
    bool shouldPrint = false;
    // Простой эвристический метод: по имени макроса мы не знаем. Вместо этого будем опираться на флаги:
    // В текущей реализации print() вызывается только из макросов, которые уже проверили свой фильтр.
    // Поэтому здесь просто печатаем, полагаясь на то, что вызывающий код уже принял решение.
    // Однако для универсальности можно передавать флаг, но проще оставить как есть.
    // Чтобы избежать двойной фильтрации, мы уже проверили флаги в макросах.
    // Этот метод вызывается только если соответствующий фильтр уже пропустил ошибку.
    // Поэтому проверку здесь не дублируем.

    std::lock_guard<std::mutex> lock(logMutex);
    if(logStream == &fileLog && (!fileLog.is_open() || fileLog.fail()))
    {
        fileLog.close();
        logStream = &std::cerr;
        if(!logErrorFlag)
        {
            logErrorFlag = true;
            *logStream << "ERROR: Log file write failed, switched to stderr\n";
        }
    }

    if(FullPrint)
        *logStream << toString();
    else
        *logStream << toStr();

    if(logStream == &fileLog && fileLog.fail())
    {
        fileLog.close();
        logStream = &std::cerr;
        if(!logErrorFlag)
        {
            logErrorFlag = true;
            *logStream << "ERROR: Failed to write to log file, switched to stderr\n";
        }
    }
    else if(logStream == &std::cerr && fileLog.fail())
    {
        fileLog.close();
    }
}

void ErrInfo::setLogToFile(const std::string& filename)
{
    std::lock_guard<std::mutex> lock(logMutex);
    if(fileLog.is_open())
        fileLog.close();
    fileLog.open(filename, std::ios::app);
    if(fileLog.is_open())
    {
        logStream = &fileLog;
        logErrorFlag = false;
        fileLog.clear();
    }
    else
    {
        logStream = &std::cerr;
        if(!logErrorFlag)
        {
            logErrorFlag = true;
            std::cerr << "ERROR: Cannot open log file '" << filename << "', using stderr\n";
        }
    }
}

void ErrInfo::setLogToCerr()
{
    std::lock_guard<std::mutex> lock(logMutex);
    if(fileLog.is_open())
        fileLog.close();
    logStream = &std::cerr;
    logErrorFlag = false;
}

void ErrInfo::flushLog()
{
    std::lock_guard<std::mutex> lock(logMutex);
    if(logStream == &fileLog && fileLog.is_open())
        fileLog.flush();
    std::cerr.flush();
}

void ErrInfo::setFatalHandler(FatalHandler handler)
{
    s_fatalHandler = handler;
}

void ErrInfo::fatal(const ErrInfo& info)
{
    flushLog();
    if(s_fatalHandler)
    {
        s_fatalHandler(info);
        std::abort(); // если обработчик вернулся – аварийно завершаемся
    }
    std::cerr << "\n!!! FATAL ERROR !!! Program will terminate.\n";
    std::abort();
}

std::string ErrInfo::getCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");

    if(TimePrecision == 3)
    {
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()) % 1000000000;
        ss << '.' << std::setfill('0') << std::setw(9) << ns.count();
    }
    else if(TimePrecision == 2)
    {
        auto mks = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;
        ss << '.' << std::setfill('0') << std::setw(6) << mks.count();
    }
    else if(TimePrecision == 1)
    {
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    }
    return ss.str();
}
