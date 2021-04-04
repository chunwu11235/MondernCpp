#include "builder.h"
#include <string>
#include <iostream>

using namespace std;

class HouseBuilder;

class House{
private:
    int floors{0};
    double price{0};
    std::string address{};
    std::string owner{};
    House();

public:
    static HouseBuilder createBuilder();
};

void demo_builder() {
    std::cout << "--- demo builder ---" << endl;
}
