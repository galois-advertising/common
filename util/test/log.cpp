#include <gtest/gtest.h>
#include "log.h"




TEST(Test, log) {
    log(LOG_LEVEL::FATAL, "%s\t%d", "log", 1);
}