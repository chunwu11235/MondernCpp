#include "factory.h"
#include "string"
#include <iostream>

struct Shape {
    std::string type{};
    double area{};
    void draw() const {
        std::cout << type << " with area " << area << std::endl;
    };
protected:
    Shape(std::string type, double area): type{type}, area{area} {};
};

class Square: public Shape {
    private:
        Square(double area): Shape{"square", area} {};
    public:
        // factory methods
        // they have the same parameters, so we are not able to overload constructors
        static Square createFromArea(double area) {
            return Square{area};
        }

        static Square createFromLength(double length) {
            return Square{length * length};
        }
};

void demo_factory() {
    std::cout << "--- Factory Methods ---\n";
    Square::createFromArea(10).draw();
    Square::createFromLength(5).draw();
}


