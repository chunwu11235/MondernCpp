#include <iostream>
#include "my_lib.h"
#include "stdio.h"

using namespace std;
using namespace Assignment;


int main(int, char**) {
    cout << "Hello, world!\n";

    int *a = new int{1};
    int *b = new int{2};

    cout << Add(a, b) << "\n";

    int *result{new int{100}};

    AddVal(a, b, result);
    cout << *result << "\n";

    cout<< *a << *b << "\n";
    Swap(a, b);
    cout<< *a << *b << "\n";

    Factorial(new int{5}, b);
    cout << *b << "\n";

}
