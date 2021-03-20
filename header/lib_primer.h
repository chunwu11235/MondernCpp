# pragma once
# ifndef LIB_PRIMER_H
# define LIB_PRIMER_H

void use_auto();
void use_decltype();
void use_function_ptr();

namespace Dynamic_mem {
    void ex_shared_ptrs();
    void ex_unique_ptr();
    void ex_weak_ptr();
}

namespace Array {
    void use_array();
    template<typename T, size_t size>
    void print(T* arr) {
        for(size_t i = 0; i < size; ++i) {
            std::cout << arr[i] << "\n";
        }
    }

    template<typename T, int size>
    void print(T (*arr)[size]) {
        for(auto & i : *arr) {
            std::cout << i << "\n";
        }
    }

    template<typename T, int size>
    T sum(T (&arr)[size]) {
        int s{};
        for(auto &i : arr) {
            s += i;
        }
        return s;
    }

}

# endif