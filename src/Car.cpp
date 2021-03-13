#include <iostream>
#include <string>

#include "Car.h"

using namespace std;

int Car::total_car = 0;

// default constructor with member initialization list
Car::Car() {
    cout << "Default Constructor\n";
    Car::total_car++;
}

Car::Car(int seat_capacity, int max_speed): Car() {
    cout << "Parameterized Constructor\n";
    this->seat_capacity = seat_capacity;
    this->max_speed = max_speed;
}

Car::Car(const Car &other): Car(other.seat_capacity, other.max_speed) {
    // deep copy
    this -> ptr = new auto(*other.get_ptr());
}

Car::~Car() {
    cout << "Destructor\n";
    Car::total_car --;
    cout << "total_car" << "\t" << total_car << "\n";

    delete this->ptr;
    this->ptr = nullptr;
}

void Car::set_ptr(int value) {
    this -> ptr = new int(value);
}

int* Car::get_ptr() const {
    return this -> ptr;
}

// const member function
string Car::get_info() const {
    return "This is a car";
}

void Car::display_info() const {
    cout << this->get_info() << "\n";
    // this->increase_seat(); // error: const methods can only use const methods
}

void Car::increase_seat() {
    seat_capacity++;
}

void Car::increase_speed() {
    max_speed++;
}






