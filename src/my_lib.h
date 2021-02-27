#ifndef MY_LIB_H
#define MY_LIB_H


int my_add(int a, int b);

// assignment 1
int Add(const int *a, const int *b);
void AddVal(const int *a, const int *b, int *result);
void Swap(int *a, int *b);
void Factorial(int *a, int *result);

void play_with_pointers();
void play_with_reference();

void pass_function_arguments();
void play_with_const();
void play_with_auto();
#endif