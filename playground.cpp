#include <iostream>
#include "my_lib.h"
#include "stdio.h"

using namespace std;

int main(int, char**) {
    cout << "Hello, world!\n";
    printf("My addition: 1 + 2 = %d\n", my_add(1, 2) );

    // uniform initialization'
    int a{10};
    printf("%d", a);

    // int a_ref{&a};
    // printf("%d", a_ref);

    int *a_ptr{new int{10}};
    cout<< a_ptr << "\t" << *a_ptr << endl;


}