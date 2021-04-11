#include "functional_decorator.h"
#include <iostream>
#include <chrono>
#include <functional>

template<typename Callable>
struct SimpleTimer{
    Callable callable;

    SimpleTimer(Callable callable): callable{callable} {};
    void operator() () {
        auto start = std::chrono::steady_clock::now();
        callable();
        auto end = std::chrono::steady_clock::now();
        std::cout << "Elapsed time: " << (end - start).count() << std::endl;
    }    

};


void func1() {
    std::cout<< "func1()\n";
}

void demo_functional_decorator() {
    std::cout << "--- Demo Functional Decorator---\n";

    std::cout << "--- void function\n";
    SimpleTimer<std::function<void()>> f1{func1};
    f1();

    
};