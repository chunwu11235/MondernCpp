# pragma once
# ifndef CAR_H
# define CAR_H

#include <string>
#include <vector>

using namespace std;

class Car{
    static int total_car; // static memebr

    private:
        int seat_capacity;
        int max_speed;
        // vector<String> passengers;
    public:
        Car(); // default constructor
        Car(int seat_capacity, int max_speed);

        string get_info() const;
        void display_info() const;
        void increase_seat();
        void increase_speed();
};


# endif