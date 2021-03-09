#include <iostream>
#include <string>

#include "Car.h"

using namespace std;

int Car::total_car = 0;

// default constructor with member initialization list
Car::Car(): seat_capacity{4}, max_speed{200} {
    cout << "Default Constructor\n";
    Car::total_car++;
}

Car::Car(int seat_capacity, int max_speed) {
    cout << "Parameterized Constructor\n";

    this->seat_capacity = seat_capacity;
    this->max_speed = max_speed;
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






