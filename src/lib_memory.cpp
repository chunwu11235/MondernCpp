#include <iostream>
#include "lib_memory.h"
#include <typeinfo>

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
    // std::cout << &that << "\n";
    // shallow copy, steal resource from "that"
    that.ptr = nullptr;
}

MyClass::MyClass(std::initializer_list<int> va_list) {
    std::cout << "MyClass(std::initializer_list<int>)\n";
    assert(va_list.size() == 2);
    auto cur = va_list.begin();
    value = *(cur++);
    delete this->ptr;
    ptr = new int{*(cur++)};
}

MyClass::~MyClass() {
    std::cout << "~MyClass()\n";
    delete ptr;
    ptr = nullptr;
}

MyClass MyClass::create() {
    std::cout << "create()\n";
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

// MyPtr
MyPtr::MyPtr() {
    std::cout << "MyPtr()\n";
}

MyPtr::MyPtr(const MyClass & myClass) {
    std::cout << "MyPtr(const MyClass &)\n";
    delete my_class_ptr;
    my_class_ptr = new MyClass(myClass);
}

MyPtr::MyPtr(MyClass && myClass) {
    std::cout << "MyPtr(MyClass &&)\n";
    delete my_class_ptr;
    if(my_class_ptr == nullptr) my_class_ptr = new MyClass;

    // note that now myClass is a l-value, i.e. we can assign values to it
    // myClass = MyClass::create(); for example
    // use std::move
    *my_class_ptr = std::move(myClass); // should invoke move operator of MyClass
}

MyPtr::MyPtr(const MyPtr& that) {
    std::cout << "MyPtr(const MyPtr &)\n";
    delete this->my_class_ptr;
    this->my_class_ptr = new MyClass(*(that.my_class_ptr)); // deep copy
}

MyPtr::MyPtr(MyPtr&& that) {
    std::cout << "MyPtr(MyPtr &&)\n";
    this->my_class_ptr = that.my_class_ptr;
    that.my_class_ptr = nullptr; // shallow copy
}

MyPtr::~MyPtr() {
    std::cout << "~MyPtr()\n";
    delete my_class_ptr;
    my_class_ptr = nullptr;
}

MyPtr & MyPtr::operator = (const MyPtr & that) {
    std::cout << "operator = (const MyPtr &)\n";
    delete my_class_ptr;
    my_class_ptr = new MyClass(*(that.my_class_ptr));
    return *this;
}

MyPtr & MyPtr::operator = (MyPtr && that) {
    std::cout << "operator = (MyPtr &&)\n";
    my_class_ptr = that.my_class_ptr;
    that.my_class_ptr = nullptr;
    return *this;
}

MyPtr & MyPtr::operator = (const MyClass & myClass) {
    std::cout << "MyPtr::operator = (const MyClass & myClass)\n";
    delete my_class_ptr;
    my_class_ptr = new MyClass(myClass); // deep copy
    return *this;
}

MyPtr & MyPtr::operator = (MyClass && myClass) {
    std::cout << "MyPtr::operator = (MyClass &&)\n";
    MyPtr(std::move(myClass));
    return *this;
}

MyClass & MyPtr::operator* () const{
    return *my_class_ptr;
}

MyClass * MyPtr::operator->() const {
    return my_class_ptr;
}

// explicit specialization should be in the .cpp file
template<>
MySmartPtr<const char *>::~MySmartPtr() {
    std::cout << "MySmartPtr<const char *>::~MySmartPtr()\n";
};

template<>
class MySmartPtr<char> {
    private:
        const char *ptr{nullptr}; // just for demo, better use std::string in C++ 11
    public:
        MySmartPtr() {
            std::cout << "MySmartPtr() of char\n";
        };

        MySmartPtr(const char *c) {
            std::cout << "MySmartPtr(const char *) of char\n";
            ptr = c;
        }

        ~MySmartPtr() {
            std::cout << "~MySmartPtr() of char\n";
        };
        void display() const {
            if(ptr) {
                std::cout << ptr << "\n";
            }else{
                std::cout << "nullptr" << "\n";
            }
        };
        void setPtr( const char* ptr) {
            delete this->ptr;
            this->ptr = ptr;
        }
        const char* getPtr() const {
            return ptr;
        };
};

template<typename T>
using Ptr = MySmartPtr<T>; // type alias
void play_with_MySmartPtr() {
    std::cout << "--- MySmartPtr Template\n";
    MySmartPtr<int> p1{};
    p1.display();

    MySmartPtr p2{100};
    p2.display();

    int num = 123;
    MySmartPtr p3{123};
    p3.display();

    std::cout << "---\n";
    auto s1 = "Hello World";

    MySmartPtr p4{s1};
    p4.display();
    std::cout << p4.getPtr() << "\n";
    std::cout << s1 << "\n";
    // warning: the copy constructor does not do a deep copy
    // need explicit specialization

    std::cout << "---\n";
    // this won't work unless we specialize the destructor
    MySmartPtr<const char*> p5;
    const char *s2 = "Hello Again";
    std::cout << s2 << "\n";
    p5.setPtr(&s2);
    p5.display();
    
    std::cout << "---\n";
    Ptr<char> p6{"Explicit Specialization"};
    p6.display();
    std::cout << p6.getPtr() << "\n";

    std::cout << "--- end\n";
}

void play_with_smart_ptr() {
    std::cout << "--- MyPtr\n";

    MyClass c1(1559, new int{201});

    std::cout << "---\n";
    MyPtr p1(c1); // invoke copy constructor of MyClass

    std::cout << "---\n";
    MyPtr p2(MyClass::create()); // invoke move constructor of MyClass

    std::cout << "---\n";
    MyPtr p3;
    p3 = MyClass::create();

    std::cout << "---\n";
    p3 = c1;
    std::cout << (*p3).getValue() << "\n"; // 1559
    std::cout << p3->getValue() << "\n"; // 1559

    std::cout << "--- initializer_list\n";
    MyClass c2{11,23};
    std::cout << c2.getValue() << "\t" << *(c2.getPtr()) << "\n"; // 11 23


    std::cout << "--- end\n";
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
    c4 = MyClass::create();
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
    MyClass c3(MyClass::create());
    std::cout << *c3.getPtr() << "\n";

    std::cout << "----\n";
    func(MyClass::create());

    std::cout << "---- std::move\n";
    func(c1);
    func(std::move(c1));
    std::cout << (c1.getPtr() == nullptr) << "\n"; 
    std::cout << *(c1.getPtr()) << "\n"; // 0, c1 still has the resource


    std::cout << "---- l-value and r-value\n";
    func(MyClass::create()); // can bind to "const MyClass &" if "MyClass &&" is not implemented 
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

    std::cout << "---- forwarding\n";

    auto c6 = MyClass::create(c1);
    auto c7 = MyClass::create(MyClass::create()); // perfect forwarding

    std::cout << "----end\n";
    // todo
    // dynamic memory allocation
    // new, new [], delete, and delete []
};





