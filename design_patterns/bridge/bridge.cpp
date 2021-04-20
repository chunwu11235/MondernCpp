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


void Ecommerce::hire() {
    cout << "Hiring some devlopers\n";
};
    
void Ecommerce::generate_revenue() {
    cout << "Selling products and ads on the online shopping platform\n";
}; 


void Ecommerce::operate() {
    cout << "Building awesome online shopping platform\n";
};