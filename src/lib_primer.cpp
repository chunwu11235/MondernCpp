#include <iostream>
#include <vector>
#include <memory>

#include "lib_primer.h"

#include "Car.h"

using namespace std;

void Array::use_array() {
    std::cout << "--- Array\n";

    int a1[] = {1,2,3};
    int a2[]{11,2,3,5, 200};
    int a[0]; // 1
    
    for(auto & i : a2) {
        std::cout << i << "\n";
    }

    std::cout << "--- begin & end\n";
    auto iter = std::begin(a2);
    while(iter < std::end(a2)) {
        std::cout << *iter << "\n";
        ++iter;
    }

    std::cout << "---\n";

    auto p2 = a2;
    auto p3 = &a2[0];
    std::cout << *p2 << "\n"; // 11, a2[0]
    std::cout << "--- print\n";
    Array::print<int, 5>(a2);
    std::cout << "--- print\n";
    Array::print<int, 5>(p3);


    std::cout << "--- non-type template\n";
    Array::print(&a2);
    std::cout << Array::sum(a2) << "\n"; // 221, sum of a2

    std::cout << "--- end\n";
}

void use_auto() {
    // check "decltype" at the same time

    // ex.2.35
    const int i = 42;
    auto j = i; // int
    const auto &k = i; // ref to const int  
    auto *p = &i; // ptr to const int
    const auto j2 = i, &k2 = i; // j2: const int, k2 : ref to const int const int &
}

void use_decltype() {
    // check "auto" at the same time

    int a = 10, &ref = a;
    decltype((a)) ref_to_int = a; // this is an expression
    decltype(a) int1;
    decltype(ref) ref_int = a;

    const int c = 100;
    int *ptr = &a;
    const int *ptr_const = &c;
    decltype(&c) ptr_to_const; // ptr to const int
    decltype(c) const_int = 2; // const int
    decltype((c)) ref_to_const = 423;
    
    decltype(ptr_to_const) ptr_to_const2;
    // decltype((ptr_to_const)) ref_ptr_const = &c; // warning is OK
    decltype((ptr_to_const)) ref_ptr_const2 = ptr_const;
    decltype(*ptr_to_const) ref_const_int = c;
    decltype(&ptr_to_const) ptr_ptr_to_const = &ptr_const;

    decltype(ref_to_const) ref_to_const2 = c;
    decltype((ref_to_const)) ref_to_const3 = c;
}

// pointers to functions
int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a*b;
}

int apply1(int a, int b, int (*fp)(int, int)) {
    cout << "func ptr as argument" << "\n";
    return (*fp)(a, b);
}

// apply1 and apply2 are the same to compliers
// function will automatically be converted to funciton ptr
int apply2(int a, int b, int f(int, int)) {
    cout << "func as argument" << "\n";
    auto fp = f; // fp is actually a ptr to function! 
    return f(a, b);
}

void use_function_ptr() {

    // basic use
    int (*pf)(int, int) = nullptr;
    pf = &add;
    pf = add; // same
    cout << pf(3, 4) << "\t" << (*pf)(3,4) << "\n";

    // implicit conversion between Function and Finction Pointer
    typedef int (*Func_Ptr)(int, int);
    typedef decltype(&add) Func_Ptr;

    typedef int (Func) (int, int);
    typedef decltype(add) Func;

    // C++ primer ex section 6.7 

    // vector<Func1> v;
    // vector<decltype(&add)> v; // same usage
    vector<decltype(pf)> v;
    v.push_back(add);
    v.push_back(multiply);

    for( const auto &f : v) {
        cout << f(2,3) << "\t";
    }
    cout << "\n";

    // functions that take functions as an argument
    cout << apply1(4, 5, &add) << " should be 9" << "\n";
    cout << apply1(4, 5, add) << " should be 9" << "\n";

    cout << apply2(4, 5, &multiply) << " should be 20" << "\n";
    cout << apply2(4, 5, &multiply) << " should be 20" << "\n";

    cout << "\n";
}

void create_shared_ptrs(vector<int*> &ptrs) {
    int *local_ptr1 = new int(0);
    auto s_ptr = make_shared<int>(1);
    ptrs[0] = local_ptr1;
    ptrs[1] = s_ptr.get();
}

void Dynamic_mem::ex_shared_ptrs() {
    
    auto p1 = make_shared<int>(10); // creat a shared pointer 
    int *p2 = p1.get(); // really bad idea, don't mix smart pointers with built-in pointers!!!

    cout << p1.use_count() << '\n'; // 1 shared_ptr so far
    auto p3{p1}; // p3 is another shared_ptr
    cout << p1.use_count() << "\t" << p3.use_count() << "\n"; // 2 and 2
    cout << p1.get() << "\t" << p2 << "\t" << p3.get() << "\n"; // addresses are the same

    auto p4 = p1;
    cout << p4.use_count() << "\t" << p1.use_count() << "\n"; // 3 3

    cout << "-----\n";
    vector<int*> ptrs{nullptr, nullptr, nullptr};
    cout << ptrs[0] << "\t" << ptrs[1] << "\t" << ptrs[2] << "\n";
    create_shared_ptrs(ptrs);
    cout << ptrs[0] << "\t" << ptrs[1] << "\t" << ptrs[2] << "\n";

    delete ptrs[0]; // OK
    ptrs[0] = nullptr;
    // smart pointers free the memory already!!!
    // delete ptrs[1]; // error
    // delete ptrs[2]; // error
    
    // shared_ptr<int> sp1 = new int(3); // error, complier doesn't know how to convert a built-in pointer to a smart pointer
    shared_ptr<int> sp1{new int{123}}; // OK

    shared_ptr<int> sp2 = make_shared<int>(13);
    // shared_ptr<int> sp3(sp2.get());
    // cout << sp2.use_count() << "\t" << sp3.use_count() << "\n"; // both are 1
    // sp2, sp3 are created separately, but they point to the same address.
    // this is going to cause error. When the program ends, sp1.get() and sp2.get() are freed twice.

    auto sp4{sp1};
    cout << sp1.use_count() << "\t" << sp4.use_count() << "\n";
    
    sp4.reset(new int(100));
    cout << *sp4 << "\t" << sp4.use_count() 
    << "\t" << *sp1 << "\t" << sp1.use_count() << "\n"; // 100 1 123 1

    cout << "\n";
}

void Dynamic_mem::ex_unique_ptr() {
    
    // doesn't support copy and assign
    // initialize with built-in pointer
    unique_ptr<int>  up1(new int(10));
    cout << *up1 << "\n";
    // auto up2 = up1; // error
    // auto up2(up1); // error

    auto ptr = up1.get();
    cout << up1.get() << "\t" << ptr << "\n";

    up1.reset(new int{100});
    cout << up1.get() << "\t" << ptr << "\n";
    // delete ptr; // error, this address is already freed by up1.reset
    // Do Not mix built-in pointers with smart pointers.
    ptr = nullptr;
}

void Dynamic_mem::ex_weak_ptr() {
    auto sp1 = make_shared<int>(10);

    weak_ptr<int> wp1(sp1);
    weak_ptr<int> wp2 = sp1;

    cout << sp1.use_count() << "\t" << wp1.use_count() << "\t" << wp2.use_count() << "\n"; // 1 1 1
    
    if(!wp2.expired()) {
        auto local_sp = wp2.lock();
        cout << sp1.use_count() << "\t" << wp2.use_count() << "\n"; // 2 2
    }
    // local_sp is cleaned
    cout << sp1.use_count() << "\t" << wp2.use_count() << "\n"; // 1 1
    // cout << *wp1 << "\n"; // cannot deref a weak_ptr!!
    cout << (wp1.expired()? -1 : (*wp1.lock()) ) << "\n";
}







