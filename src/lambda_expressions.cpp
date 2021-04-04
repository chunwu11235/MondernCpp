#include <iostream>
#include "lambda_expressions.h"

template<typename T>
using Consumer = void (&)(T); // function object

template<typename T>
using ConsumerPtr = void (*)(T); // function pointer

template<typename T, size_t size, typename Consumer>
void ForEach(T (&arr)[size], Consumer consumer) {
    std::cout << "ForEach " << typeid(T).name() << "\t" << typeid(Consumer).name() << "\n";
    for( T& t : arr) {
        consumer(t);
    }
}

template<typename T>
void my_print(T t) {
    std::cout << t << "\n";
}

// function object, make it callable
template<typename T>
class MyConsumer {
    public:
        void operator()(T t) {
            std::cout << t << "\n";
        }

        static MyConsumer create() {
            return MyConsumer{};
        }
};

void demo_lambda() {
    std::cout << "--- Lambda\n";

    int arr[]{1,2,3,4,5};
    Consumer<int> c1 = my_print;
    ForEach(arr, c1);
    std::cout << "---\n";
    ConsumerPtr<int> fptr1 = my_print; // function pointer
    ForEach(arr, fptr1);

    std::cout << "--- Lambda internal\n";
    ForEach(arr, MyConsumer<int>::create());

    std::cout << "--- Lambda\n";
    ForEach(arr, [](int i) {
        std::cout << i << "\n";
    });


    std::cout << "--- Capture List\n";
    // work with local variables in Lambda expressions
    int sum{0};
    // pass sum by reference, otherwise, it is passed by value
    ForEach(arr, [&sum](int i){
        sum += i;
    });

    std::cout << sum << "\n";
    std::cout << "--- end\n";
    
}