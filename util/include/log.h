#pragma once
enum class LOG_LEVEL { FATAL, ERROR, WARNING, INFO, DEBUG, TRACE };
void log(LOG_LEVEL loglevel, const char * fmt, ...);