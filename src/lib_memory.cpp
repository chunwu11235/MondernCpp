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
    std::cout << "creat()\n";
    return MyClass(0, new int{100});
}

const int* MyClass::getPtr() const{
    std::cout << &(this->ptr) << "\n";
    return this->ptr;
}

int MyClass::getValue() const {
    return this->value;
}

void func(const MyClass &myClass) {
    std::cout << "func(const MyClass &)\n";
}

void func(MyClass &&myClass) {
    std::cout << "func(MyClass &&)\n";
}

MyClass func2() {
    std::cout << "func2()\n";
    MyClass temp(1, new int{2});
    std::cout << temp.getPtr() << "\t" << "\n";
    return temp;
}

void play_with_resources() {
    std::cout << "----\n";
    MyClass c1;
    std::cout << "----\n";
    MyClass c2(c1);
    std::cout << "----\n";
    MyClass c3(MyClass::creat());
    std::cout << *c3.getPtr() << "\n";

    std::cout << "----\n";
    func(MyClass::creat());

    std::cout << "----\n";
    func(c1);
    func(std::move(c1));

    std::cout << "----\n";
    auto c4 = func2();
    std::cout << c4.getPtr() << "\n";

    std::cout << "----end\n";
    // todo
    // dynamic memory allocation
    // new, new [], delete, and delete []
};

