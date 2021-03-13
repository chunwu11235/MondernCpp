#include <iostream>
#include "lib_memory.h"


MyClass::MyClass() {
    std::cout << "MyClass()\n";
}

MyClass::MyClass(int value, int *ptr): value{value}, ptr{ptr} {
    std::cout << "MyClass(int, int *)\n";
}

MyClass::MyClass(const MyClass & that): value{that.value} {
    std::cout << "MyClass(const MyClass &)\n";
    // deep copy
    if(that.ptr)
        ptr = new auto(*that.ptr);
}

MyClass::MyClass(MyClass && that): value{that.value}, ptr{that.ptr} {
    std::cout << "MyClass(MyClass &&)\n";
    // shallow copy, steal resource from "that"
    that.ptr = nullptr;
}

MyClass::~MyClass() {
    std::cout << "~MyClass()\n";
    delete ptr;
    ptr = nullptr;
}

MyClass MyClass::creat() {
    MyClass temp = MyClass(10, new int{100});
    return temp;
}

const int* MyClass::getPtr() const{
    return this->ptr;
}

int MyClass::getValue() const {
    return this->value;
}

void play_with_resources() {
    std::cout << "----\n";
    MyClass c1;
    std::cout << "----\n";
    MyClass c2(c1);
    std::cout << "----\n";
    MyClass c3(MyClass::creat());
    // std::cout << *c3 << "\n";


    std::cout << "----end\n";
    // todo
    // dynamic memory allocation
    // new, new [], delete, and delete []
};

