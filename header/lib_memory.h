#pragma once
#ifndef LIB_MEMORY_H
#define MY_MEMORY_H


class MyClass {
    private:
        int value{0};
        int *ptr{nullptr}; // always initialize ptr

    public:
        MyClass();
        MyClass(int value, int *ptr);
        MyClass(const MyClass &other); // copy constructor
        MyClass(MyClass && other); // move constructor
        ~MyClass();

        static MyClass creat();

        const int * getPtr() const;
        int getValue() const;
};

// my implementation of smart_ptr
class MyPtr {
    private:
        MyClass *my_class_ptr{nullptr};
    public:
        // todo

};


void play_with_resources();



#endif