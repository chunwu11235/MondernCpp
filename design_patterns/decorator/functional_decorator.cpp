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
        std::cout << "Elapsed time: " 
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() 
            << " nanosecond " << std::endl;
    }    

};


void func1() {
    std::cout<< "func1()\n";
}

double myAdd(double a, double b) {
    return a + b;
}


template<typename R, typename... Args>
struct GeneralTimer{
    std::function<R(Args...)> func;

    GeneralTimer(std::function<R(Args...)> func): func{func} {};
    R operator() (Args... args) {
        auto start = std::chrono::steady_clock::now();
        R res = func(args...);
        auto end = std::chrono::steady_clock::now();
        std::cout << "Elapsed time: " 
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() 
            << " nanosecond " << std::endl;
        
        return res;
    }
};



void demo_functional_decorator() {
    std::cout << "--- Demo Functional Decorator---\n";

    std::cout << "--- void function\n";
    SimpleTimer<std::function<void()>> f1{func1};
    f1();

    std::cout << "--- general function\n";
    GeneralTimer<double, double, double> f2{myAdd};
    auto res = f2(10, 20);
    std::cout << res << std::endl; // 30

    std::cout << "--- combined with Lambda expression\n";
    GeneralTimer<int, int> f3{
        [](int a) {
            return a * 10;
        }
    };

    std::cout << f3(10) << std::endl; // 100;


};