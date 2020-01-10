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
void log(LOG_LEVEL loglevel, const char *fmt, ...);
#define LOGLINE(x) LOGLINE_(x)
#define LOGLINE_(x) #x

#ifdef _DEBUG
#define TRACE(fmt, ...) log(LOG_LEVEL::TRACE, "%c" __FILE__"][" LOGLINE(__LINE__) "]" fmt , '[', __VA_ARGS__);
#define TRACE(fmt) log(LOG_LEVEL::TRACE, "[" __FILE__"][" LOGLINE(__LINE__) "]" fmt);
#else
#define TRACE(fmt, ...)
#endif

#ifdef _DEBUG
#define DEBUG(fmt, ...) log(LOG_LEVEL::DEBUG, "[" __FILE__"][" LOGLINE(__LINE__) "]" fmt,  __VA_ARGS__);
#else
#define DEBUG(fmt, ...)
#endif

#define INFO(fmt, ...) log(LOG_LEVEL::INFO, "[" __FILE__"][" LOGLINE(__LINE__) "]" fmt,  __VA_ARGS__);

#define WARNING(fmt, ...) log(LOG_LEVEL::WARNING, "[" __FILE__"][" LOGLINE(__LINE__) "]" fmt,  __VA_ARGS__);

#define ERROR(fmt, ...) log(LOG_LEVEL::ERROR, "[" __FILE__"][" LOGLINE(__LINE__) "]" fmt,  __VA_ARGS__);

#define FATAL(fmt, ...) log(LOG_LEVEL::FATAL, "[" __FILE__"][" LOGLINE(__LINE__) "]" fmt,  __VA_ARGS__);