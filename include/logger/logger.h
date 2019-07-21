#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <mutex>

namespace Logging
{
    #define LOG_LEVEL_NONE 100
    #define LOG_LEVEL_FATAL 50
    #define LOG_LEVEL_ERROR 40
    #define LOG_LEVEL_WARN 30
    #define LOG_LEVEL_INFO 20
    #define LOG_LEVEL_DEBUG 10
    #define LOG_LEVEL_DEBUG_LOW 9
    #define LOG_LEVEL_DEBUG_MID 8
    #define LOG_LEVEL_DEBUG_HIGH 7
    #define LOG_LEVEL_ALL 0

    #define LOG(x, y, z) Logging::Logger::getInstance().Log(__FILE__, __LINE__, x, y, z)
    #define LOG_FATAL(x) LOG(LOG_LEVEL_FATAL, "FATAL", x)
    #define LOG_ERROR(x) LOG(LOG_LEVEL_ERROR, "ERROR", x)
    #define LOG_WARN(x) LOG(LOG_LEVEL_WARN, "WARN", x)
    #define LOG_INFO(x) LOG(LOG_LEVEL_INFO, "INFO", x)
    #define LOG_DEBUG(x) LOG(LOG_LEVEL_DEBUG, "DEBUG", x)
    #define LOG_DEBUG_LOW(x) LOG(LOG_LEVEL_DEBUG_LOW, "DEBUG_LOW", x)
    #define LOG_DEBUG_MID(x) LOG(LOG_LEVEL_DEBUG_MiD, "DEBUG_MID", x)
    #define LOG_DEBUG_HIGH(x) LOG(LOG_LEVEL_DEBUG_HIGH, "DEBUG_HIGH", x)

    #ifndef LOGGER_DEFAULT_LOG_LEVEL
    #define LOGGER_DEFAULT_LOG_LEVEL LOG_LEVEL_DEBUG_HIGH
    #endif

    #ifndef LOGGER_DEFAULT_LOG_TYPE
    #define LOGGER_DEFAULT_LOG_TYPE LOG_TYPE::CONSOLE
    #endif

    #ifndef LOGGER_DEFAULT_LOG_FILE
    #define LOGGER_DEFAULT_LOG_FILE "Log.txt"
    #endif

    #ifndef LOGGER_DEFAULT_DECIMAL_PRECISION
    #define LOGGER_DEFAULT_DECIMAL_PRECISION DECIMAL_PRECISION::THREE
    #endif

    typedef enum LOG_TYPE
    {
        CONSOLE = 0,
        FILE = 1,
        CONSOLE_FILE = 2
    }LogType;

    typedef enum DECIMAL_PRECISION
    {
        ZERO = 0,
        ONE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7

    }DecimalPrecision;

    class Logger
    {
        public:
            static Logger& getInstance();

            void updateLogLevel(const int logLevel);
            void updateLogType(LogType logType);
            void updateLogFile(std::string& logFile);
            void updateDecimalPrecision(DecimalPrecision decimalPrecision);

            void Log(const char* file, const int line, const int logLevel, const char* tag, const char* text);
            void Log(const char* file, const int line, const int logLevel, const char* tag, std::string& text);
            void Log(const char* file, const int line, const int logLevel, std::string& tag, const char* text);
            void Log(const char* file, const int line, const int logLevel, std::string& tag, std::string& text);

            Logger(const Logger& arg) = delete; 
            Logger(const Logger&& arg) = delete;
            Logger& operator=(const Logger& arg) = delete;
            Logger& operator=(const Logger&& arg) = delete;

        private:
            Logger();
            ~Logger();

            void lock();
            void unlock();
            void openFile();
            void closeFile();
            void log(std::string& data);
            void logToConsole(std::string& data);
            void logToFile(std::string& data);
            std::string getCurrentTime();

            int                     m_LogLevel;
            LogType                 m_LogType;
            DecimalPrecision        m_DecimalPrecision;
            
            std::ofstream           m_File;
            std::string             m_LogFile;
            std::mutex              m_Mutex;
    };
}
#endif