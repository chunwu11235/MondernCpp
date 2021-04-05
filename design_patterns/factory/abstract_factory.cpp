#include "factory.cpp"
#include <iostream>
#include <memory>
using namespace std;

// virtual class, i.e., interface
class AbstractProductA {
    public:
    AbstractProductA() {
        cout << "AbstractProductA()\n";
    };

    virtual ~AbstractProductA() = 0;

    virtual void operate() = 0;
};

//A pure virtual destructor must have a definition, 
//since all base class destructors are always called when the derived class is destroyed
AbstractProductA::~AbstractProductA() {
    cout << "~AbstractProductA()\n";
}

class ProductA1 : public AbstractProductA {
    public:
    ~ProductA1() override {
        cout << "~ProductA1()\n";
    }
    void operate() override {
        cout << "ProductA1 is operating\n";
    }
};

class AbstractProductB {
    public:
    virtual ~AbstractProductB() = 0;
};


class AbstractFactory {
    public:
        // pure virtual methods, i.e. abstract methods
        virtual shared_ptr<AbstractProductA> createProductA() const = 0;
        virtual shared_ptr<AbstractProductB> createProductB() const = 0;
};


// todo: make this singleton
class Factory1 {
    public:
    shared_ptr<AbstractProductA> createProductA() const{
        return make_shared<ProductA1>();
    }

    shared_ptr<AbstractProductB> createProductB() const{
        return nullptr;
    }

};

void demo_abstract_factory() {
    std::cout << "--- Abstract Factory ---\n"; 
}
