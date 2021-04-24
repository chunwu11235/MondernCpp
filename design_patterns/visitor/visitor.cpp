#include "visitor.hpp"
#include <iostream>
using namespace std;

void Mountain::accept(Visitor* v) {
    v -> visit(this);
}

void Lake::accept(Visitor* v) {
    v -> visit(this);
}

void City::accept(Visitor* v) {
    v -> visit(this);
}

void Visitor::_visit(Location* location) {
    cout << this->name << " is passing " << location->name << endl;
    if(location->next != nullptr) {
        location->next->accept(this);
    }
}

void Visitor::visit(Location* location) {
    _visit(location);
}

void Hiker::visit(Mountain* location) {
    cout << this->name << " is hiking at " << location->name << endl;
    if(location->next != nullptr) {
        location->next->accept(this);
    }
}

void Foodie::visit(City* location) {
    cout << this->name << " is eating at " << location->name << endl;
    if(location->next != nullptr) {
        location->next->accept(this);
    }
}


void demo_visitor() {
    cout << "--- DEMO VISITOR --- \n";

    auto path1 = City("Las Vegas",
        make_shared<Mountain>("Grand Canyon", 
        make_shared<City>("LA", 
        make_shared<Lake>("Lake Tahoe", 
        nullptr))));

    Hiker hiker{"Anderson"};
    Foodie foodie("Jason");
    

    path1.accept(&hiker);
    cout << "---\n";
    path1.accept(&foodie);


    cout << "--- PROGRAM END --- \n";
}