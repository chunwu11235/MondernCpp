#pragma once
#ifndef DESIGN_PATTERNS_BRIDGE
#define DESIGN_PATTERNS_BRIDGE

#include <memory>
#include <iostream>
using namespace std;
// Pimpl: pointer to implementation
template<typename T>
struct Pimpl {
private:
    unique_ptr<T> implementation;
public:
    template<typename ...Args>
    Pimpl(Args&&... args): implementation{new T{forward<args>(args)...}} {}

    T& operator* () {
        return *implementation; 
    }

    T* operator-> () {
        return implementation.get();
    }
};


struct IBusiness {
    virtual void hire() = 0;
    virtual void generate_revenue() = 0; 
    virtual void operate() = 0;
};

struct Trading : IBusiness{
    Trading() {};
    void hire() override;
    void generate_revenue() override;
    void operate() override;
};

struct Ecommerce : IBusiness{
    Ecommerce() {};
    void hire() override;
    void generate_revenue() override;
    void operate() override;
};

// Bridge Pattern
template<typename T>
struct Company {
private:
    Pimpl<T> business;

public:
    template<typename... Args>
    Company(Args&&... args): business{forward<args>(args)...} {};

    void run() {
        business->operate();
        business->generate_revenue();
    }
    
    void expand() {
        business->hire();
        business->operate();
        business->generate_revenue();
    }
};

void demo_bridge();

#endif