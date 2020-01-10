#include <string>
#include <boost/log/trivial.hpp>
#include "log.h"


void log(LOG_LEVEL loglevel, const char *fmt, ...) {
    if (fmt == nullptr) {
        return;
    }
    va_list args;
    char buf[2048];
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);
    switch(loglevel) {
    case LOG_LEVEL::TRACE: BOOST_LOG_TRIVIAL(trace)<< buf;break;
    case LOG_LEVEL::DEBUG: BOOST_LOG_TRIVIAL(debug)<< buf;break;
    case LOG_LEVEL::INFO: BOOST_LOG_TRIVIAL(info)<< buf;break;
    case LOG_LEVEL::WARNING: BOOST_LOG_TRIVIAL(warning)<< buf;break;
    case LOG_LEVEL::ERROR: BOOST_LOG_TRIVIAL(error)<< buf;break;
    case LOG_LEVEL::FATAL: BOOST_LOG_TRIVIAL(fatal)<< buf;break;
    };
}




