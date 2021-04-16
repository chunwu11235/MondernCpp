#include "builder.h"
#include <string>
#include <iostream>
#include <memory>

using namespace std;

class House; // declare

template<typename T>
struct IBuilder{
    virtual T build() = 0;
    virtual unique_ptr<T> buildPtr() = 0;
};

// define
class House{
private:
    int floors{0};
    double price{0};
    std::string address{};
    House() {}; // force clients to use the builder API

    void setFloors(const int floors) {
        this->floors = floors;
    }

    void setPrices(const double price) {
        this->price = price;
    }

    template<typename T>
    void setAddress(T&& address) {
        this->address = std::forward<T>(address);
    }
    
public:
    class HouseBuilder : public IBuilder<House> {
    private:
        House* house{nullptr};
    public:
        HouseBuilder(): house{new House{}} {}

        // fluent builder
        HouseBuilder& withFloors(int floors) {
            house->setFloors(std::move(floors));
            return *this;
        }

        HouseBuilder& withPrice(double price) {
            house->setPrices(std::move(price));
            return *this;
        }

        template<typename T>
        HouseBuilder& withAddress(T&& address) {
            house->setAddress(std::forward<T>(address));
            return *this;
        }

        House build() override{
            return std::move(*house);
        }

        unique_ptr<House> buildPtr() override {
            return make_unique<House>(std::move(*house));
        }
    };

public:
    static HouseBuilder createBuilder() {
        return House::HouseBuilder{};
    };

friend std::ostream& operator << (std::ostream& os, const House& house);
};

std::ostream& operator << (std::ostream& os, const House& house) {
    return os 
        << "House at " << house.address
        << " has " << house.floors << " floors"
        << " and worths " << house.price
        << std::endl;
};

void demo_builder() {
    std::cout << "--- demo builder ---" << endl;

    auto house1 = House::createBuilder()
        .withAddress(std::string("123 A Street, AAA City, GG 5566"))
        .withFloors(19)
        .withPrice(15e5)
        .build();
    
    std::cout << house1;

    auto housePtr2 = House::createBuilder()
        .withAddress("123 Earth Street, Gotham City, DC 1812")
        .buildPtr();

    std::cout << *housePtr2;

}
