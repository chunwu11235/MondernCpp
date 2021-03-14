#pragma once
#ifndef LIB_MEMORY_H
#define MY_MEMORY_H


class MyClass {
    private:
        int value{0};
        int *ptr{nullptr}; // always initialize ptr
    public:
        MyClass();
        MyClass(int &value);
        MyClass(int &&value);
        MyClass(int value, int *ptr);
        MyClass(const MyClass &other); // copy constructor
        MyClass(MyClass && other); // move constructor
        ~MyClass();

        MyClass operator +(const MyClass & that ) const; // operator overloading
        MyClass & operator ++(); // pre-increment
        MyClass operator ++(int); // post-increment
        bool operator == (const MyClass & that) const;

        MyClass & operator = (const MyClass & that); // assign
        MyClass & operator = (MyClass && that); // move

        static MyClass creat();

        const int * getPtr() const;
        int getValue() const;

        void setPtr(int v);
        void setValue(int v);
};

// my implementation of smart_ptr
class MyPtr {
    private:
        MyClass *my_class_ptr{nullptr};
    public:
        // todo

};

void play_with_operator_overloading();

void play_with_resources();



#endif