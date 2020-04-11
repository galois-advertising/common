#include <gtest/gtest.h>
#include "net.h"
#include "log.h"
TEST(Test, net) {
    timeval tv = {0, 0};
    galois::net::select_wrap(0, nullptr, nullptr, nullptr, &tv);
    TRACE("Test net done", "");
}