#include <iostream>

#include "stdio.h"
#include "stdlib.h"

#include "lib_primer.h"
#include "lib_101.h"

using namespace std;

void assignment1();

int main(int, char**) {
    // assignment1();
    // use_function_ptr();

    // Dynamic_mem::ex_shared_ptrs();
    // Dynamic_mem::ex_unique_ptr();
    Dynamic_mem::ex_weak_ptr();
}

void assignment1() {
    using namespace Assignment;
    cout << "Hello, world!\n";

    int *a = new int{1};
    int *b = new int{2};

    cout << Add(a, b) << "\n";

    int *result{new int{100}};

    AddVal(a, b, result);
    cout << *result << "\n";

    cout<< *a << *b << "\n";
    Swap(a, b);
    cout<< *a << *b << "\n";

    Factorial(a, b);
    cout << *b << "\n";


    cout << *a << "\n";
    cout << *b << "\n";

    // after deleting, we might still be able to access the object 
    // the behavior is undefined. The purpose of deleting is to tell
    // the memory manager that these addresses are free to be re-allocat
    delete a;
    delete b;
    a = nullptr;
    b = nullptr;
}