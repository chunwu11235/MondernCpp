#include <iostream>
#include "lib_memory.h"

MyClass::MyClass() {
    std::cout << "MyClass()\n";
}

MyClass::MyClass(int& value): value{value} {
    std::cout << "MyClass(int)\n";
}

// check the result with/without this one
MyClass::MyClass(int&& value): value{value} {
    std::cout << "MyClass(int &&)\n";
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
    std::cout << &that << "\n";
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
    return this->ptr;
}

int MyClass::getValue() const {
    return this->value;
}

void MyClass::setPtr(int v) {
    if(this->ptr == nullptr)
        this->ptr = new int;
    *(this->ptr) = v;
}

void MyClass::setValue(int v) {
    this->value = v;
}

// overloading as a memebr method
MyClass MyClass::operator +(const MyClass &that) const{
    return MyClass(this->value + that.value);
}

MyClass operator -(const MyClass & c1, const MyClass & c2) {
    return MyClass(c1.getValue() - c2.getValue());
}

MyClass & MyClass::operator ++() {
    ++(this->value);
    return *this; // return by reference (l-value)
}

MyClass MyClass::operator ++(int) {
    auto temp = MyClass(*this);
    ++(this->value);
    return temp;
}

bool MyClass::operator ==(const MyClass & that) const{
    if(this->value != that.value) return false;
    if(this->ptr == nullptr) {
        return that.ptr == nullptr;
    }else{
        if(that.ptr == nullptr) {
            return false;
        }else{
            return *(this->ptr) == *(that.ptr);
        }
    }
}

MyClass & MyClass::operator = (const MyClass & that) {
    std::cout << "operator = (const MyClass &)\n";
    if(this != &that) {
        this->value = that.value;
        delete this->ptr;
        this->ptr = new int(*(that.ptr)); // deep copy
    }
    return *this;
}

MyClass & MyClass::operator = (MyClass && that) {
    std::cout << "operator = (MyClass &&)\n";
    this->value = that.value;
    delete this->ptr;
    this->ptr = that.ptr;
    that.ptr = nullptr;
    return *this;
}

// global functions
void func(MyClass &myClass) {
    std::cout << "func(MyClass &)\n";
}

void func(const MyClass &myClass) {
    std::cout << "func(const MyClass &)\n";
}

// comment out this function and run again
void func(MyClass &&myClass) {
    std::cout << "func(MyClass &&)\n";
}

MyClass func2() {
    std::cout << "func2()\n";
    MyClass temp(1, new int{2});
    std::cout << temp.getPtr() << "\t" << "\n";
    // no additional copy will be created because of "copy ellision"
    // by default, compliers enable copy ellision
    return temp; 
}

void play_with_operator_overloading() {
    std::cout << "---operator overloading\n";

    MyClass c1(19);
    MyClass c2(1);
    std::cout << "--- local +\n";
    std::cout << (c1+c2).getValue() << "\n"; // 20


    std::cout << "--- global -\n";
    std::cout << (c1-c2).getValue() << "\n"; // 18


    std::cout << "--- global -\n";
    // pay attention to this one
    // if we implement MyClass(int &&)
    // this should invoke move constructor instead of a parameterized constructor
    std::cout << (10-c2).getValue() << "\n"; // 9, from global overload

    std::cout << "--- pre/post increment\n";
    // pre/post increment
    std::cout << (++c1).getValue() << "\t" << c1.getValue() << "\n"; // 20 20
    std::cout << (c1++).getValue() << "\t" << c1.getValue() << "\n"; // 20 21

    std::cout << (c1 == c1) << "\t" << (c1 == c2) << "\n";
    
    std::cout << "--- copy\n";
    // copy and assign
    c1.setPtr(123);
    auto c3 = c1; // copy
    std::cout << c1.getPtr() << "\n";
    std::cout << c3.getPtr() << "\n"; // deep copy
    std::cout << (c1 == c3) << "\n"; // true

    std::cout << "--- assignment\n";
    MyClass c4;
    c4 = c1; // assign
    std::cout << c1.getPtr() << "\n";
    std::cout << c4.getPtr() << "\n"; // deep copy
    std::cout << (c1 == c4) << "\n"; // true

    std::cout << "--- move\n";
    c4 = MyClass::creat();
    std::cout << *(c4.getPtr()) << "\n"; // 100

    std::cout << "---end\n";

}

void play_with_resources() {
    std::cout << "----\n";
    MyClass c1;
    c1.setPtr(123);
    std::cout << "----\n";
    MyClass c2(c1);
    std::cout << "----\n";
    MyClass c3(MyClass::creat());
    std::cout << *c3.getPtr() << "\n";

    std::cout << "----\n";
    func(MyClass::creat());

    std::cout << "---- std::move\n";
    func(c1);
    func(std::move(c1));
    std::cout << (c1.getPtr() == nullptr) << "\n"; 
    std::cout << *(c1.getPtr()) << "\n"; // 0, c1 still has the resource?


    std::cout << "---- l-value and r-value\n";
    func(MyClass::creat()); // can bind to "const MyClass &" if "MyClass &&" is not implemented 
    func(c1);

    const MyClass &ref = c1;
    func(ref);

    
    std::cout << "----\n";
    std::cout << &c2 << "\n";
    auto c4 = MyClass(std::move(c2));
    std::cout << (c2.getPtr() == nullptr) << "\n"; // 1, c2's resources has been stolen
    
    std::cout << "----\n";
    auto c5 = func2();
    std::cout << c5.getPtr() << "\n";

    std::cout << "----end\n";
    // todo
    // dynamic memory allocation
    // new, new [], delete, and delete []
};





