#include "flyweight.hpp"
#include <iostream>
#include <memory>
#include "string.h"
#include <unordered_map>

using namespace std;

// shared between objects
// should be immutable
class Flyweight{
    const string name;
    const int id;
    static int _id;
public:
    Flyweight(const string& name): name{name}, id{++_id}{
        cout << "Flyweight()\n";
    };
    void operation(const string& job) {
        cout << id << " " << name << " is operating " << job << endl;
    }
};

int Flyweight::_id = 0;


struct FlyweightFactory {
private:
    static unordered_map<string, Flyweight> flyweightPool;
    FlyweightFactory() {};
public:
    static Flyweight& getFlyweight(const string& name) {
        if(flyweightPool.find(name) == flyweightPool.end()) {
            flyweightPool.emplace(name, Flyweight(name));
        }
        return flyweightPool.find(name)->second;
    }
};

unordered_map<string, Flyweight> FlyweightFactory::flyweightPool{};

void demo_flyweight() {
    cout << "--- DEMO FLYWEIGHT --- \n";

    auto p1 = FlyweightFactory::getFlyweight("Eason");
    p1.operation("mission impossible 11");
    FlyweightFactory::getFlyweight("Anna").operation("KGB");
    FlyweightFactory::getFlyweight("Eason").operation("CIA");

}