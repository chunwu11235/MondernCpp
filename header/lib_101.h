#pragma once
#ifndef LIB_101_H
#define LIB_101_H

int my_add(int a, int b);

namespace Assignment {
    int Add(const int *a, const int *b);
    void AddVal(const int *a, const int *b, int *result);
    void Swap(int *a, int *b);
    void Factorial(int *a, int *result);
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
    template<typename T>
    T add(T x, T y); 
}


void play_with_templates();

void play_with_pointers();
void play_with_reference();

void pass_function_arguments();
void play_with_const();
void play_with_auto();
void play_with_overloading();

#endif