#include "dynamic_decorator.h"
#include <iostream>
#include "string.h"
#include <sstream>


using namespace std;

struct Car{
    static int id;
    int _id;
    Car(): _id{++Car::id} {};

    virtual void run() const {
        cout << "---Car id: " << this->_id << "\n";
        cout << to_ostringstream().str() << " is running\n";
    };
    virtual ostringstream to_ostringstream() const = 0;
};
int Car::id = 0;

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
struct CarWithTurbo : public Car {
    Car& car;
    std::string turbo{};
    
    CarWithTurbo(Car& car, std::string turbo): car{car}, turbo{turbo} {};
    
    ostringstream to_ostringstream() const override {
        ostringstream oss = car.to_ostringstream();
        oss << " with turbo: " << turbo;
        return oss;
    };
};

struct CarWithSnowTires : public Car {
    Car& car;
    
    CarWithSnowTires(Car& car): car{car} {};
    
    ostringstream to_ostringstream() const override {
        ostringstream oss = car.to_ostringstream();
        oss << " with snow tires";
        return oss;
    };
};


void demo_dynamic_decorator() {
    std::cout << "--- Demo Dynamic Decorator---\n";

    Coupe coupe1;
    SUV suv1;

    coupe1.run();
    suv1.run();

    CarWithTurbo turboCoupe{coupe1, string{"twin turbo"}};
    turboCoupe.run();
    // turboCoupe.car.runInSportMode(); // not allowed

    CarWithSnowTires snowCar1{turboCoupe};
    snowCar1.run();

    CarWithSnowTires snowCar2{suv1};
    snowCar2.run();
}