#include "builder.h"
#include <string>
#include <iostream>
#include <memory>

using namespace std;

class House{
private:
    int floors{0};
    double price{0};
    std::string address{};
    House() {};

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
    static class HouseBuilder {
    private:
        House* house{nullptr};
    public:
        HouseBuilder(): house{new House{}} {}
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

        House build() {
            return std::move(*house);
        }
    };

public:
    static HouseBuilder createBuilder() {
        return House::HouseBuilder{};
    };
};

void demo_builder() {
    std::cout << "--- demo builder ---" << endl;

    auto house1 = House::createBuilder()
        .withAddress(std::string("123 A Street, AAA City, GG 88888"))
        .withFloors(19)
        .withPrice(15e5)
        .build();

}
