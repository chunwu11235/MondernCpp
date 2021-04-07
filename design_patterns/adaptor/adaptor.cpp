#include "adaptor.h"
#include <iostream>

struct ComplexMachine {
    virtual void operate() const {
        std::cout << "operating a complex machine\n";
    };
};

struct SuperComputer : public ComplexMachine {
    void operate() const {
        std::cout << "operating super computer\n";
    }
};

struct SimpleMachine {
    virtual void turnOn() const = 0;
};


// use multiple inheritance
struct Adaptor1 : SimpleMachine, ComplexMachine {
    virtual void turnOn() const {
        operate();
    };
};

// use composition, better
struct Adaptor2 : SimpleMachine {
    const ComplexMachine& machine;
    Adaptor2(const ComplexMachine& machine): machine{machine} {};

    void turnOn() const override{
        machine.operate();
    }
};

struct Client {
    void useSimpleMachine(const SimpleMachine& machine) {
        machine.turnOn();
    }
};

void demo_adaptor() {
    std::cout << "--- Demo Adaptor --- \n";

    SuperComputer superComputer;

    Client kid;
    kid.useSimpleMachine(Adaptor2(superComputer));
    kid.useSimpleMachine(Adaptor1());
}

