#include <iostream>
#include "Oop.h"


Base::Base() {
    std::cout << "Base()\n";
}

Base::Base(int n_private, int n_protected): n_private{n_private}, n_protected{n_protected} {
    std::cout << "Base(int, int)\n";
}

Base::~Base() {
    std::cout << "~Base()\n";
}

void Base::show() const{
    std::cout << "Base::show()\n";
    std::cout << n_private << "\t" << n_protected << "\n";
}

Derived::Derived() {
    std::cout << "Derived()\n";
}

Derived::Derived(int n_derived): n_derived{n_derived} {
    std::cout << "Derived(int)\n";
}

Derived::Derived(int n_derived, int n_private, int n_protected): Base(n_private, n_protected) {
    // Base(n_private, n_protected); // no, need to use memebr initialization
    std::cout << "Derived(int, int, int)\n";
    this->n_derived = n_derived;
} 

Derived::~Derived() {
    std::cout << "~Derived()\n";
}

void Derived::show() const {
    std::cout << "Derived::show()\n";
    Base::show();
    std::cout << n_derived << "\n"; // cannot see n_private
}

void demo_oop() {
    std::cout << "--- oop\n";

    std::cout << "---\n";
    // see the order of constructors and destructors
    Derived d1;

    std::cout << "---\n";
    Derived d2{10}; // still invoke Base()

    std::cout << "---\n";
    Derived d3{1, 2, 3};
    d3.show();

    std::cout << "--- end\n";
}