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
        MyClass(std::initializer_list<int> va_list);
        ~MyClass();

        MyClass operator +(const MyClass & that ) const; // operator overloading
        MyClass & operator ++(); // pre-increment
        MyClass operator ++(int); // post-increment
        bool operator == (const MyClass & that) const;

        MyClass & operator = (const MyClass & that); // assign
        MyClass & operator = (MyClass && that); // move

        static MyClass create(); // factory method

        // demo of perfect forwarding
        // remember to delcare and define templates in header files
        template<typename T> static MyClass create(T && myClass) {
            std::cout << "template<typename T> MyClass MyClass(T&&)\n";
            return MyClass(std::forward<T>(myClass));
        };

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
        MyPtr();
        MyPtr(const MyClass & myClass);
        MyPtr(MyClass && myClass);
        MyPtr(const MyPtr & that); // copy
        MyPtr(MyPtr && that); // move
        ~MyPtr();
        MyPtr & operator = (const MyPtr & that); // assign
        MyPtr & operator = (MyPtr && that); // move

        MyPtr & operator = (const MyClass & myClass);
        MyPtr & operator = (MyClass && myClass);

        MyClass & operator *() const;
        MyClass * operator ->() const;
};

template<typename T>
class MySmartPtr {
    private:
        T *ptr{nullptr};
    public:
        MySmartPtr() {
            std::cout << "MySmartPtr() of " << typeid(T).name() << "\n";
        };

        MySmartPtr(const T & t) {
            std::cout << "MySmartPtr(const T &) of " << typeid(T).name() << "\n";
            ptr = new T{t};
        }

        MySmartPtr(T&& t) {
            std::cout << "MySmartPtr(T&&) of " << typeid(T).name() << "\n";
            ptr = new T{std::forward<T>(t)};
        }

        ~MySmartPtr() {
            std::cout << "~MySmartPtr() of " << typeid(T).name() << "\n";
            delete ptr;
        };
        void display() const {
            if(ptr) {
                std::cout << ptr << "\t" << *ptr << "\n";
            }else{
                std::cout << "nullptr" << "\n";
            }
        };
        void setPtr( T* ptr) {
            delete this->ptr;
            this->ptr = ptr;
        }
        T* getPtr() const {
            return ptr;
        };
};

void play_with_MySmartPtr();

void play_with_smart_ptr(); // my implementation of smart_ptr

void play_with_operator_overloading();

void play_with_resources();



#endif