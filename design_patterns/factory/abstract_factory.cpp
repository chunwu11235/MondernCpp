#include "abstract_factory.h"
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

// interface
class Component{
private:
    string material{};
    double length{};
    double width{};
protected:
    Component(string material, double length, double width): 
    material{material}, length{length}, width{width} {};

friend std::ostream& operator << (std::ostream& os, const Component c) {
    return os << "material: " << c.material
        << " length: " << c.length
        << " width: " << c.width << std::endl; 
};
};


struct Wall : public Component{    
    Wall(string material, double length, double width):
     Component(material, length, width) {};
};

struct Door : public Component{
    Door(string material, double length, double width):
     Component(material, length, width) {};
};

struct AbstractFactory {
    virtual Wall createWall(double length, double width) const = 0; 
    virtual Door createDoor(double length, double width) const = 0;
};

struct WoodFactory : AbstractFactory {
    Wall createWall(double length, double width) const override {
        return Wall("wood", length, width);
    }; 
    virtual Door createDoor(double length, double width) const override {
        return Door("wood", length, width);
    };
};

struct StoneFactory : AbstractFactory {
    Wall createWall(double length, double width) const override {
        return Wall("stone", length, width);
    }; 
    virtual Door createDoor(double length, double width) const override {
        return Door("stone", length, width);
    };
};


struct Client {
    void buildHouse(AbstractFactory&& factory ) {
        auto door = factory.createDoor(5, 10);
        auto wall = factory.createWall(10, 10);
        cout << "building house with door " << door 
        << " and wall "<< wall << endl;
    };
};


void demo_abstract_factory() {
    std::cout << "--- Abstract Factory ---\n"; 
    Client client{};

    std::cout << "--- Stone House ---\n";
    client.buildHouse(StoneFactory{});

    std::cout << "--- Wood House --- \n";
    client.buildHouse(WoodFactory{});
}
