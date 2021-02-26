#include <iostream>
#include "my_lib.h"
#include "stdio.h"
#include "string"


using namespace std;

// void play_with_pointers();

int main(int, char**) {
    cout << "Hello, world!\n";
    printf("My addition: 1 + 2 = %d\n", my_add(1, 2) );

    play_with_pointers();

}