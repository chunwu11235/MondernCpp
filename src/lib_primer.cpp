#include <iostream>
#include <vector>
#include <memory>

#include "lib_primer.h"

using namespace std;

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

void create_ptrs(vector<int*> &ptrs) {
    int *local_ptr1 = new int(0);
    auto s_ptr = make_shared<int>(1);
    auto u_ptr = make_unique<int>(2);
    ptrs[0] = local_ptr1;
    ptrs[1] = s_ptr.get();
    ptrs[2] = u_ptr.get();
}

void create_ptrs2(vector<float*> &ptrs) {
    // these ptrs are local variables
    float *local_ptr1 = new float(0);
    auto s_ptr = make_shared<float>(1);
    auto u_ptr = make_unique<float>(2);
    ptrs.push_back(local_ptr1);
    ptrs.push_back(s_ptr.get());
    ptrs.push_back(u_ptr.get());
}

void Dynamic_mem::smart_ptrs() {
    
    auto p1 = make_shared<int>(10); // creat a shared pointer 
    int *p2 = p1.get();
    *p2 = 100;

    cout << p1.use_count() << '\n'; // 1 shared_ptr so far
    auto p3{p1}; // p3 is another shared_ptr
    cout << p1.use_count() << "\t" << p3.use_count() << "\n"; // 2 and 2
    cout << p1.get() << "\t" << p2 << "\t" << p3.get() << "\n"; // addresses are the same


    cout << "-----\n";
    vector<int*> ptrs{nullptr, nullptr, nullptr};
    cout << ptrs[0] << "\t" << ptrs[1] << "\t" << ptrs[2] << "\n";
    create_ptrs(ptrs);
    cout << ptrs[0] << "\t" << ptrs[1] << "\t" << ptrs[2] << "\n";

    delete ptrs[0]; // OK
    // smart pointers free the memory already!!!
    // delete ptrs[1]; // error
    // delete ptrs[2]; // error
    
    // cout << "-----\n";
    // vector<float*> ptrs2;
    // create_ptrs2(ptrs2);
    // cout << ptrs2[0] << "\t" << ptrs2[1] << "\t" << ptrs2[2] << "\n";
    // cout << *ptrs2[0] << "\t" << *ptrs2[1] << "\t" << *ptrs2[2] << "\n";
    
    // delete ptrs2[0];
    // delete ptrs2[1]; // error
    // // delete ptrs2[2];

    cout << "\n";
}



