#pragma once
#ifndef LIB_101_H
#define LIB_101_H

#include <string>
#include <vector>

int my_add(int a, int b);

namespace Assignment {
    int Add(const int *a, const int *b);
    void AddVal(const int *a, const int *b, int *result);
    void Swap(int *a, int *b);
    void Factorial(int *a, int *result);

    std::string ToUpper(const std::string & str);
    std::string ToLower(const std::string & str);

    enum class Case{SENSITIVE, INSENSITIVE};
    size_t Find(const std::string &source, const std::string &search_string,
        Case searchCase = Case::INSENSITIVE, size_t offset = 0);
    
    std::vector<int> FindAll(const std::string & source, std::string & target,
        Case searchCase = Case::INSENSITIVE, size_t offset = 0);
}

namespace My_Function{
    // function overloading
    // Defaults should always go in the header file, if the function is declared in a header file
    void function_overloading(int a = 100);
    void function_overloading(double a);
    void overload_ref(int &ref);
    void overload_ref(const int &ref);
}

namespace Generic{
    // function and class templates should be declared and defined in the header files
    // will only be instantiated if certain templates are invoked
    // ex, if add(1,2) was invoked, the compiler will instantiate add(int, int)
    template<typename T>
    T add(T x, T y) {
        return x + y;
    }

    template<typename T, int size>
    int sum(T* arr);
}

void demo_nested_classes();

void assignment_sec8();

void play_with_templates();

void play_with_pointers();
void play_with_reference();

void pass_function_arguments();
void play_with_const();
void play_with_auto();
void play_with_overloading();

#endif