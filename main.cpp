#include <iostream>

#include "stdio.h"
#include "stdlib.h"

#include "lib_primer.h"
#include "lib_101.h"
#include "lib_memory.h"

#include "Car.h"
#include "Oop.h"
#include "lambda_expressions.h"

using namespace std;

void assignment1();
void oop_basics();

int main(int, char**) {

    demo_lambda();
    // play_with_MySmartPtr();
    // Array::use_array();
    // demo_oop();

    // play_with_smart_ptr();
    // play_with_operator_overloading();
    // play_with_resources();

    // assignment1();
    // use_function_ptr();

    // Dynamic_mem::ex_shared_ptrs();
    // Dynamic_mem::ex_unique_ptr();
    // Dynamic_mem::ex_weak_ptr();

    // oop_basics();
}

void oop_basics() {
    cout << "---- car1\n";
    Car car1;
    car1.display_info();

    cout << "---- car 2\n";
    const Car car2(4, 10);
    // car2.increase_seat(); // error can only use const method
    car2.display_info();
    cout << Car::get_total_car() << "\n"; // 2

    cout << "---- car3\n";
    auto car3 = make_shared<Car>(); // 3 cars
    car3->display_info();
    car3.reset(); // invoke Destructor, 2 cars
    car3.reset(new Car(10,10));
    cout << Car::get_total_car() << "\n"; // 3
    
    cout << "---- car4\n";
    // copy constructor and deep copy
    car1.set_ptr(5566);
    auto ptr_car1 = car1.get_ptr();

    Car car4(car1); // 4 cars
    auto ptr_car4 = car4.get_ptr();

    cout << ptr_car1 << "\t" << ptr_car4 << "\n"; // should not be the same
    // if car4 is a shallow copy, then the ptr will be deleted twice and cause an error
    cout << "-----end\n";
}

void assignment1() {
    using namespace Assignment;
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

    Factorial(a, b);
    cout << *b << "\n";


    cout << *a << "\n";
    cout << *b << "\n";

    // after deleting, we might still be able to access the object 
    // the behavior is undefined. The purpose of deleting is to tell
    // the memory manager that these addresses are free to be re-allocate
    delete a;
    delete b;
    a = nullptr;
    b = nullptr;
}