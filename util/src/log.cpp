#include <string>
#include <boost/log/trivial.hpp>
#include "log.h"


void log(LOG_LEVEL loglevel, const char * file, unsigned int line, const char *fmt, ...) {
    va_list args;
    char buf[2048];
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);
    switch(loglevel) {
    case LOG_LEVEL::TRACE: BOOST_LOG_TRIVIAL(trace)<<"["<<file<<"]["<<line<<"]"<< buf;break;
    case LOG_LEVEL::DEBUG: BOOST_LOG_TRIVIAL(debug)<<"["<<file<<"]["<<line<<"]"<< buf;break;
    case LOG_LEVEL::INFO: BOOST_LOG_TRIVIAL(info)<<"["<<file<<"]["<<line<<"]"<< buf;break;
    case LOG_LEVEL::WARNING: BOOST_LOG_TRIVIAL(warning)<<"["<<file<<"]["<<line<<"]"<< buf;break;
    case LOG_LEVEL::ERROR: BOOST_LOG_TRIVIAL(error)<<"["<<file<<"]["<<line<<"]"<< buf;break;
    case LOG_LEVEL::FATAL: BOOST_LOG_TRIVIAL(fatal)<<"["<<file<<"]["<<line<<"]"<< buf;break;
    };
}




