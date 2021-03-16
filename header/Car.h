# pragma once
# ifndef CAR_H
# define CAR_H

#include <string>
#include <vector>

using namespace std;

class Car{
    static int total_car; // static memebr

    private:
        int seat_capacity{4};
        int max_speed{100};
        int *ptr = nullptr;
        // vector<String> passengers;
    public:
        
        Car(); // default constructor
        Car(int seat_capacity, int max_speed);
        Car(const Car &other); // copy constructor
        ~Car(); // destructor

        int* get_ptr() const;
        void set_ptr(int value);
        string get_info() const;
        void display_info() const;
        void increase_seat();
        void increase_speed();
        
        static int get_total_car() {
            return Car::total_car;
        }
};

# endif