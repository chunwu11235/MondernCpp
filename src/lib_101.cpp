#include<iostream>
#include "lib_101.h"

using namespace std;

using namespace My_Function;
namespace My_Function{
    void function_overloading(int a) {
        cout << "for int" << "\n";
    }

    void function_overloading(double a) {
        cout << "for double" << "\n";
    }

    void overload_ref(const int &a) {
        cout << "for ref to const int" << "\n";
    }

    void overload_ref(int &a) {
        cout << "for ref to int" << "\n";
    }
}



int Assignment::Add(const int *a, const int *b) {
    return *a + *b;
}

void Assignment::AddVal(const int *a, const int *b, int *result) {
    *result = *a + *b;
}

void Assignment::Swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Assignment::Factorial(int *a, int *result) {
    int ans = 1;
    for(;*a > 1; *a -= 1) {
        ans *= *a;
    }
    *result = ans;
}

std::string Assignment::ToUpper(const std::string & str) {
    std::string temp{str};
    for(auto& c : temp) {
        c = toupper(c);
    }
    return temp;
}

size_t Assignment::Find(const std::string & source, const std::string &search_string,
Case searchCase, size_t offset) {
    if(searchCase == Case::INSENSITIVE) {
        std::string s = Assignment::ToUpper(source);
        std::string t = Assignment::ToUpper(search_string);
        return s.find(t, offset);
    }else{
        return source.find(source, offset);
    }
}

std::vector<int> Assignment::FindAll(const std::string & source, std::string &target,
Case searchCase, size_t offset) {
    std::vector<int> v;
    std::string s;
    std::string t;
    if(searchCase == Case::INSENSITIVE) {
        s = ToUpper(source);
        t = ToUpper(target);
    }else{
        s = source;
        t = target;
    }

    while(offset < s.length()) {
        int i = s.find(t, offset);
        if(i == std::string::npos) break;
        v.push_back(i);
        offset = i + 1;
    }
    return v;
}

int my_add(int a, int b) {
    return a + b;
}

void assignment_sec8() {
    std::cout << "--- sec 8 assignment\n";
    std::string s1 = "Hello World";
    std::string s2 = Assignment::ToUpper(s1);
    cout << s2 << "\n";
    cout << Assignment::ToUpper("this is another test case!") << "\n";

    std::cout << "---\n";
    assert(Assignment::Find(s1, "world") == 6);
    assert(Assignment::Find(s1, "world", Assignment::Case::INSENSITIVE, 7) == std::string::npos);

    std::cout << "---\n";
    std::string s = "Hello Hello World";
    std::string t = "hello";
    auto res = Assignment::FindAll(s, t);
    for(auto & i : res) {
        cout << i << ',';
    }
    std::cout << "\n";


    std::cout << "--- end\n";
}

class Enclose{
public:
    struct Nested{};
    static Nested getNested() {
        return Nested{};
    }
};
 
void demo_nested_classes()
{
    auto nested1 = Enclose::getNested();
    auto nested2 = Enclose::Nested{};
};


void play_with_templates() {
    using namespace Generic;
    std::cout << "--- templates\n";
    auto s1 = add(2.9, 3.3);
    std::cout << s1 << "\t" << typeid(s1).name() << "\n";

    auto s2 = add(1, 4); // type deduced at compile time
    std::cout << s2 << "\t" << typeid(s2).name() << "\n";

    std::cout << "--- end\n";
}

void play_with_pointers() {
    // uniform initialization'
    int a{10};
    cout << a << "\t" << &a << "\n";

    int a_ref{a};
    cout << a_ref << "\t" << &a_ref << "\n";
    
    // basic overpation of pointers
    int *a_ptr{&a};
    cout << a_ptr << "\t" << *a_ptr << "\n";

    // nullptr
    int *a_ptr2 = nullptr; // always use nullptr;
    // *a_ptr2 = 100; // cannot read and write a nullptr
    a_ptr2 = &a; // need to assign address first
    *a_ptr2 = 5;
    cout << a << "\n";

    cout << *a_ptr2 << "\n";

    *a_ptr = 5; // same as &a = 5, same as a = 5
    cout << a << "\n";

    int arr[]{1,2,3,4,5};
    cout << arr << "\t" << arr[2] << "\n";
    int *arr_ptr = arr;
    cout << arr_ptr << "\t" << arr_ptr[3] << "\n";

    // void pointer
    void *ptr = &a;
    char *c_ptr = new char{'c'};
    cout << (void * ) &c_ptr << "\t" << *c_ptr << "\n"; // void * to print the address of char ptr
    delete c_ptr;
    c_ptr = nullptr;

    // ptr of a ptr
    // ptr is a object that holds the address of another object
    int num = 1123;
    int *n_ptr = &num;
    cout << n_ptr << "\t"<< &n_ptr << "\n";
    *n_ptr = 100; // assign 100 to the address of n_ptr
    cout << n_ptr << "\n"; // address should be the same
    
    // since ptr itself is a object, we can have ptr to ptr
    int **n_pptr = &n_ptr;
    cout << n_pptr << "\t"<< &n_ptr << "\n"; // should be the same

    int *&n_ptr_ref{n_ptr};
    cout << n_ptr_ref << "\t" << n_ptr << "\n";

    n_ptr_ref = &a; // this is OK, all point to a
    cout << &a << "\t" << n_ptr_ref << "\t" << n_ptr << 
    "\t" << *n_pptr << "\n";
    
    cout << a << "\n"; // should still be 5
    *n_ptr_ref = 50; // a shhold be 50
    cout << a << "\t";
    **n_pptr = 101; // a should be 101
    cout << a << "\t";


    cout << "\n";
}
void play_with_reference() {
    int x = 10;
    int &x_ref = x;

    // int &ref = 10; // not allow, must bind to a variable not a literal
    cout << &x << "\t" << &x_ref; // same address, x and x_ref are identifiers

    cout << "\n";
}
void pass_function_arguments() {

    // local function
    int *ptr = new int{10};
    cout << ptr << "\t" << &ptr << "\t" << *ptr;
    
    // c++ doesn't support local function
    // we need to use the lambda feature in modern c++ (11/14/17)
    auto local_function = [] (int *ptr_local) {
        // the values of ptr and ptr_local are the same
        // but the addresses are not, ptr_local and ptr are two different variables!
        // pass by value in this case
        cout << ptr_local << " address of the local ptr: " << &ptr_local 
            << "\t" << *ptr_local << "\n";

        int *&ptr_local_ref = ptr_local;
        ptr_local_ref = new int{10000}; // ptr_local now point to 10000;
        delete ptr_local_ref;
        ptr_local_ref = nullptr;

        // we have changed the value of ptr_local
        cout << "this has changed " << ptr_local << " address of the local ptr: " << &ptr_local
            << "\t" << *ptr_local << "\n";

    };

    local_function(ptr);       
    // nothing has changed for ptr
    cout << ptr << "\t" << &ptr << "\t" << *ptr;
    cout <<"\n";

    delete ptr;
    ptr = nullptr;
}
void play_with_const() {

    // ref to const 
    const int n = 10;
    int n2 = n; // this is OK, copy value
    const int &ref_to_const = n;
    // int &ref = n; // not allow
    
    int num = 10;
    int *ptr = &num;
    cout << ptr << "\t" << &ptr << "\t" << *ptr << "\n"; 
    
    // what is the difference?
    const int *ptr_to_const = ptr; // pointer to a const int
    *ptr = 100; // allow
    // *ptr_to_const = 1000; // not allow
    
    cout << ptr << "\t" << &ptr << "\t" << *ptr << "\n"; 
    cout << ptr_to_const << "\t" << &ptr_to_const << "\t" << *ptr_to_const << "\n"; 

    ptr_to_const = new int{123}; // ptr_to_const itself is not const, it is the stuff it points to a const.
    cout << ptr_to_const << "\t" << &ptr_to_const << "\t" << *ptr_to_const << "\n"; 
    delete ptr_to_const;
    ptr_to_const = nullptr;

    int const *ptr_to_const2 = ptr; // the same as ptr_to_const
    cout << ptr_to_const2 << "\t" << &ptr_to_const2 << "\t" << *ptr_to_const2 << "\n"; 
    // *ptr_to_const2 = 13; // not allow
    ptr_to_const2 = new int{321}; // allow
    cout << ptr_to_const2 << "\t" << &ptr_to_const2 << "\t" << *ptr_to_const2 << "\n"; 
    delete ptr_to_const2;
    ptr_to_const2 = nullptr;
    
    // const pointer
    const int const_int = 2;
    // int *const const_ptr = &const_int; // not allow
    int *const const_ptr = ptr; // const pointer to int
    *const_ptr = 1231; // OK

    // const_ptr = &const_int; // not allow
    const int *const const_ptr_to_const =  &const_int; // OK

    cout << ptr << "\t" << &ptr << "\t" << *ptr << "\n"; 
    cout << const_ptr << "\t" << &const_ptr << "\t" << *const_ptr << "\n"; 

    // mix all
    int x = 5 ;
    const int *ptr1 = &x ;
    const int *&p_ref1 = ptr1 ;

    int *const ptr2 = &x;
    const int *const &p_ref2 = ptr2; // attention!   
}
void play_with_auto() {
    int a = 10;
    const int const_a = 12;
    auto ref = a;
    auto ref_const = const_a; // b is a copy of const_a

    // auto is conservative
    auto ptr = &a;
    const auto ptr2 = &const_a;
    auto w = &ptr2;

    auto list = {"12", }; // initialization list
    // auto list{"123","12"}; // can only take one element in this way

    // use with range-based for loop
    int arr[] = {1,2,3,4};
    for(const auto &i : arr) {
        cout << i;
        // i = 100; not allow
    }
    cout << "\n";

    for(auto &i : arr) {
        cout << i;
        i *= 2;
    }
    cout << "\n";

    // check arr, now is {2,4,6,8}
    // how it works internally?
    auto &&range = {1,2,3,4};
    auto b = begin(arr);
    auto e = end(arr);
    for(;b != e; b++) {
        auto temp = *b;
        cout << *b << "\t";
    }
    cout << "\n";

    for(auto i : {1,3,5,7}) {
        cout << i << "\t";
    }
    cout << "\n";

    // for loop with pointer and containers
    for(auto cur = begin(arr); cur != end(arr); cur++) {
        *cur *= 100; 
        cout << *cur << "\t";
    }

    cout << "\n";
    for(const int* cur = begin(arr); cur != end(arr); cur++) {
        // *cur *= 100; 
        cout << *cur << "\t";
    }

    cout << "\n";
}

void play_with_overloading() {
    function_overloading();
    function_overloading(10);
    function_overloading(10.0);
    int a = 10;
    int &ref = a;
    const int &ref_to_const = a;
    overload_ref(ref);
    overload_ref(ref_to_const);
}

