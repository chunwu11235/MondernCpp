#include <iostream>
#include "my_lib.h"
#include "stdio.h"

using namespace std;

int main(int, char**) {
    cout << "Hello, world!\n";
    printf("My addition: 1 + 2 = %d\n", my_add(1, 2) );
}
