#include <iostream>
#include "my_lib.h"
#include "stdio.h"
#include "string"


using namespace std;

int main(int, char**) {
    cout << "Hello, world!\n";
    printf("My addition: 1 + 2 = %d\n", my_add(1, 2) );

    // uniform initialization'
    int a{10};
    cout << a << "\t" << &a << "\n";

    int a_ref{a};
    cout << a_ref << "\t" << &a_ref << "\n";
    
    int *a_ptr{&a};
    cout << a_ptr << "\t" << *a_ptr << "\n";

    int *a_ptr2 = nullptr; // always use nullptr;
    // *a_ptr2 = 100; // cannot read and write a nullptr
    a_ptr2 = &a; // need to assign address first
    *a_ptr2 = 5;
    cout << a << "\n";

    cout << *a_ptr2 << "\n";

    *a_ptr = 5; // same as &a = 5, same as a = 5
    cout << a << "\n";

    int arr[]{1,2,3,4,5};
    cout << arr << "\t" << arr[2] << "\n";
    int *arr_ptr = arr;
    cout << arr_ptr << "\t" << arr_ptr[3] << "\n";

    // void pointer
    void *ptr = &a;

    char *c_ptr = new char{'c'};
    cout << (void * ) &c_ptr << "\t" << *c_ptr << endl; // void * to print the address of char ptr
}