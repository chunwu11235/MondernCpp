#include "prototype.h"
#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <typeinfo>
using namespace std;

template<typename T>
struct Prototype {
    virtual T clone() const = 0;
};

struct Car : Prototype<Car> {
private:
    double value{0};
    std::string maker{};
    std::string model{};
    int year{};
    Car() {};
    Car(double value, const std::string maker, const std::string model, int year): 
    value{value}, maker{maker}, model{model}, year{year} {};
    Car(const Car& other): Car{other.value, other.maker, other.model, other.year} {};

public:
    // prototypes
    static Car model1;
    static Car model2;

    Car clone() const {
        // can also be implemented using serialization and deserialization 
        return Car{value, maker, model, year};
    };

    void setValue(double v) {
        value = v;
    };

    void setYear(int y) {
        year = y;
    };

    friend std::ostream& operator << (std::ostream& os, const Car& car) {
        return os << "Car value: " << car.value << " maker: " << (car.maker)
        << " model: " << car.model << " year: " << car.year << std::endl;
    }

};

std::string Tesla{"Tesla"};
std::string Pagani{"Pagani"};

Car Car::model1{10000, Tesla, "ModelG", 1880}; 
Car Car::model2{500000, Pagani, "Zonda", 2010};

void demo_prototype() {
    std::cout << "--- Demo Prototype ---\n";

    auto car1 = Car::model1.clone();
    car1.setValue(500);

    auto car2 = Car::model1.clone();
    car2.setValue(10105);

    std::cout << car1 << car2 << Car::model1 << std::endl;
    std::cout << Car::model2 << std::endl;

}