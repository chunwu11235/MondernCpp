#include "bridge.hpp"
#include <iostream>

using namespace std;


// hide implementations from clients
void Trading::hire() {
    cout << "Hiring some quants\n";
};
    
void Trading::generate_revenue() {
    cout << "Trading with secret strategies\n";
}; 


void Trading::operate() {
    cout << "Building awesome systemic trading framework\n";
};