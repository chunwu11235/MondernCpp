#include "prototype.h"
#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <typeinfo>
using namespace std;

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
using namespace boost;


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

    friend class boost::serialization::access;
    template<typename archive>
    void serialize(archive& ar, const unsigned int version) {
        ar & value; // & acts as both >> and <<. This can be used for both (de)serialization
        ar & maker; // boost takes care of pointer
        ar & model;
        ar & year;
    }

public:
    // prototypes
    static Car model1;
    static Car model2;

    // // clone with serialization
    // static Car clone(const Car& other) {
    //     ostringstream oss;
    //     archive::text_oarchive oa(oss);
    //     oa << other;
    //     string s = oss.str();
    //     cout << s << endl;

    //     istringstream iss(s);
    //     archive::text_iarchive ia(iss);

    //     Car car;
    //     ia >> car;
    //     return car;
    // }

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