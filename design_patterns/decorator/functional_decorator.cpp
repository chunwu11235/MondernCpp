#include "functional_decorator.h"
#include <iostream>
#include "string.h"
#include <sstream>

using namespace std;

struct Car{
    virtual void run() const {
        cout << to_ostringstream().str() << " is running\n";
    };
    virtual ostringstream to_ostringstream() const = 0;
};

struct Coupe : public Car {
    ostringstream to_ostringstream() const override {
        ostringstream oss;
        oss << "a coupe";
        return oss;
    };

    void runInSportMode() const {
        std::cout << "a coupe is running in sport mode\n";
    };
};

struct SUV : public Car {
    ostringstream to_ostringstream() const override {
        ostringstream oss;
        oss << "a SUV";
        return oss;
    };

    void runInAWDMode() const {
        std::cout << "a SUV is running in all-wheel-drive mode\n";
    };
};

// decorator
// struct CarWithTurbo : public Car {
//     Car& car;
//     std::string turbo{};

//     CarWithTurbo(Car& car, std::string turbo): car{car}, turbo{turbo} {};
//     void run() const override {
//         car.run();
//     }
// };



void demo_functional_decorator() {
    std::cout << "--- Demo Functional Decorator---\n";

    Coupe coupe1;
    SUV suv1;

    coupe1.run();
    suv1.run();
    
};