#include "bridge.hpp"
#include <iostream>

// only access to .hpp
// the implementations in .cpp is hidden
void demo_bridge() {
    std::cout << "--- DEMO BRIDGE---\n";
    Company<Trading> hfc{};
    hfc.run();

    Company<Ecommerce> afirm{};
    afirm.expand();
    
}