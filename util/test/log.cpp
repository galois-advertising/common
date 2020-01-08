#include <gtest/gtest.h>
#include "log.h"


TEST(Test, log) {
    TRACE("%s\t%d", "log", 1);
    DEBUG("%s\t%d", "log", 1);
    INFO("%s\t%d", "log", 1);
    WARNING("%s\t%d", "log", 1);
    ERROR("%s\t%d", "log", 1);
    FATAL("%s\t%d", "log", 1);
}