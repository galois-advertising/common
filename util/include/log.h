#pragma once
enum class LOG_LEVEL
{
    FATAL,
    ERROR,
    WARNING,
    INFO,
    DEBUG,
    TRACE
};
void log(LOG_LEVEL loglevel, const char * file, unsigned int line, const char *fmt, ...);

#ifdef _DEBUG
#define TRACE(msg, ...) log(LOG_LEVEL::TRACE, __FILE__, __LINE__, msg, __VA_ARGS__);
#else
#define TRACE(msg, ...)
#endif

#ifdef _DEBUG
#define DEBUG(msg, ...) log(LOG_LEVEL::DEBUG, __FILE__, __LINE__, msg, __VA_ARGS__);
#else
#define DEBUG(msg, ...)
#endif

#define INFO(msg, ...) log(LOG_LEVEL::INFO, __FILE__, __LINE__, msg, __VA_ARGS__);

#define WARNING(msg, ...) log(LOG_LEVEL::WARNING, __FILE__, __LINE__, msg, __VA_ARGS__);

#define ERROR(msg, ...) log(LOG_LEVEL::ERROR, __FILE__, __LINE__, msg, __VA_ARGS__);

#define FATAL(msg, ...) log(LOG_LEVEL::FATAL, __FILE__, __LINE__, msg, __VA_ARGS__);