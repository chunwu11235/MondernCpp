#include "my_lib.h"

int my_add(int a, int b) {
    return a + b;
}

int Add(const int *a, const int *b) {
    return *a + *b;
}

void AddVal(const int *a, const int *b, int *result) {
    *result = *a + *b;
}

void Swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Factorial(int *a, int *result) {
    int ans = 1;
    for(;*a > 1; *a -= 1) {
        ans *= *a;
    }
    *result = ans;
}

