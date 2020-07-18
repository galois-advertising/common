#include <iostream>
#include "singleton.h"
#include <gtest/gtest.h>

class test {
    int aa;
    float bb;
    double cc;
public:
    test() : aa(0), bb(0.0), cc(0.0) {

    }
    test(int a, float b, double c) : 
        aa(a), bb(b), cc(c) {
    };
    void print() {
        std::cout<<aa<<"|"<<bb<<"|"<<cc<<std::endl;
    };
};


TEST(Test, singleton) {
    using namespace galois::common;
    auto inst = singleton<test>::instance(1, 2.3, 3.4);
    inst->print();
    auto inst2 = get_singleton<test>();
    inst2->print();
}