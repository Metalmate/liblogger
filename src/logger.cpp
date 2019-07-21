#include "logger/logger.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <mutex>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <ctime>

using namespace std;
using namespace Logging;

const char* timeFormat = "%d-%m-%Y %X";

Logger::Logger()
{
   m_LogLevel = LOGGER_DEFAULT_LOG_LEVEL;
   m_LogType = LOGGER_DEFAULT_LOG_TYPE;
   m_LogFile = LOGGER_DEFAULT_LOG_FILE;
   m_DecimalPrecision = LOGGER_DEFAULT_DECIMAL_PRECISION;
}

Logger::~Logger()
{

}

Logger& Logger::getInstance()
{
   static Logger instance;
   return instance;
}

void Logger::Log(const char* file, const int line, const int logLevel, const char* tag, const char* text)
{
    if (logLevel >= m_LogLevel)
    {
        string log;
        log.append("[" + getCurrentTime() + "]");
        log.append("[");
        log.append(tag);
        log.append("][");
        log.append(file);
        log.append("][" + to_string(line) + "]");
        log.append(text);
        this->log(log);
    }
}

void Logger::updateLogLevel(const int logLevel)
{
   m_LogLevel = logLevel;
}

void Logger::updateLogType(LogType logType)
{
   m_LogType = logType;
}

void Logger::updateLogFile(std::string& logFile)
{
   m_LogFile = logFile;
}

void Logger::updateDecimalPrecision(DecimalPrecision decimalPrecision)
{
   m_DecimalPrecision = decimalPrecision;
}

void Logger::Log(const char* file, const int line, const int logLevel, const char* tag, std::string& text)
{
    Log(file, line, logLevel, tag, text.data());
}

void Logger::Log(const char* file, const int line, const int logLevel, std::string& tag, const char* text)
{
    Log(file, line, logLevel, tag.data(), text);
}

void Logger::Log(const char* file, const int line, const int logLevel, std::string& tag, std::string& text)
{
    Log(file, line, logLevel, tag.data(), text.data());
}

string Logger::getCurrentTime()
{
    // By default, the precision is three decimals.
    // divider is used to convert the linux timestamp (which has a precision of .0000001 seconds / 7 decimals) to the desired precision.
    long transformed, millis;
    long divider = 10000;
    long moduloQuotient = 1000;
    string format = "%s.%03d";

    switch(m_DecimalPrecision)
    {
        case DECIMAL_PRECISION::ONE:
            divider *= 100;
            moduloQuotient /= 100;
            format.replace(5, 1, "1");
            break;
        case DECIMAL_PRECISION::TWO:
            divider *= 10;
            moduloQuotient /= 10;
            format.replace(5, 1, "2");
            break;
        case DECIMAL_PRECISION::FOUR:
            divider /= 10;
            moduloQuotient *= 10;
            format.replace(5, 1, "4");
            break;
        case DECIMAL_PRECISION::FIVE:
            divider /= 100;
            moduloQuotient *= 100;
            format.replace(5, 1, "5");
            break;
        case DECIMAL_PRECISION::SIX:
            divider /= 1000;
            moduloQuotient *= 1000;
            format.replace(5, 1, "6");
            break;
        case DECIMAL_PRECISION::SEVEN:
            divider /= 10000;
            moduloQuotient *= 10000;
            format.replace(5, 1, "7");
            break;
    }

    using std::chrono::system_clock;
    auto currentTime = std::chrono::system_clock::now();
    char buffer[80];

    if (m_DecimalPrecision >= DECIMAL_PRECISION::ONE)
    {
        transformed = currentTime.time_since_epoch().count() / divider;
        millis = transformed % moduloQuotient;
    }

    std::time_t tt;
    tt = system_clock::to_time_t ( currentTime );
    auto timeinfo = localtime (&tt);
    strftime(buffer, 80, "%d-%m-%Y %H:%M:%S", timeinfo);
    
    if (m_DecimalPrecision >= DECIMAL_PRECISION::ONE)
    {
        sprintf(buffer, format.c_str(), buffer, millis);
    }

    return std::string(buffer);
}

void Logger::lock()
{
    m_Mutex.lock();
}

void Logger::unlock()
{
    m_Mutex.unlock();
}

void Logger::openFile()
{
    m_File.open(m_LogFile.c_str(), ios::out|ios::app);
}

void Logger::closeFile()
{
    m_File.close();
}

void Logger::log(std::string& data)
{
    switch(m_LogType)
    {
        case LOG_TYPE::CONSOLE:
            logToConsole(data);
            break;
        case LOG_TYPE::FILE:
            logToFile(data);
            break;
        case LOG_TYPE::CONSOLE_FILE:
            logToConsole(data);
            logToFile(data);
            break;

    }
}

void Logger::logToConsole(std::string& data)
{
    cout << data << endl;
}

void Logger::logToFile(std::string& data)
{
    lock();
    openFile();
    m_File << data << endl;
    closeFile();
    unlock();
}