#include <gtest/gtest.h>
#include <string>
#include <chrono>
#include <thread>
#include "log.h"
#include "cache.h"


TEST(Test, cache) {
    galois::common::cache<std::string, std::string> c(3);
    auto calulate = [](std::string& input) -> std::string {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        return input + "_done";};
    int cnt = 5;
    while (--cnt) {
        auto res = c.get(std::string("hahah"), calulate, std::string("hahah"));
        std::cout<<"["<<cnt<<"]"<<res<<std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(100));

}