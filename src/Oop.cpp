#include <iostream>
#include "Oop.h"

Base::Base() {
    std::cout << "Base()\n";
}

Base::~Base() {
    std::cout << "~Base()\n";
}


Derived::Derived() {
    std::cout << "Derived()\n";
}

Derived::Derived(int n_derived): n_derived{n_derived} {
    std::cout << "Derived(int)\n";
}

Derived::~Derived() {
    std::cout << "~Derived()\n";
}

void demo_oop() {
    std::cout << "--- oop\n";

    std::cout << "---\n";
    // see the order of constructors and destructors
    Derived d1;

    std::cout << "---\n";
    Derived d2{10}; // still invoke Base()

    std::cout << "--- end\n";
}