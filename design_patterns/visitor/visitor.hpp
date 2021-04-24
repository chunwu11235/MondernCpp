#pragma once
#ifndef DESIGN_PATTERNS_VISITOR
#define DESIGN_PATTERNS_VISITOR

#include <string>
#include <memory>
#include <iostream>
using namespace std;

struct Visitor;

struct Location {
    virtual ~Location() {
        cout << "~Location()\n"; // for debuggin
    };
    virtual void accept(Visitor* visitor) = 0;
   
    string name;
    shared_ptr<Location> next;
    Location(const string& name, const shared_ptr<Location> next): 
        name{name}, next{next} {
            cout << "Location()\n"; // for debuggin
    };
};

struct Mountain : Location{
    Mountain(const string& name, const shared_ptr<Location> next): Location(name, next) {};
    void accept(Visitor* visitor) override;
};

struct City : Location {
    City(const string& name, const shared_ptr<Location> next): Location(name, next) {};
    void accept(Visitor* visitor) override;
};

struct Lake : Location {
    Lake(const string& name, const shared_ptr<Location> next): Location{name, next} {};
    void accept(Visitor* visitor) override;
};

struct Visitor {
    string name;
    Visitor(const string& name): name{name} {};
    void _visit(Location* location);
    virtual void visit(Location* location);
    virtual void visit(City* location) {_visit(location);};
    virtual void visit(Mountain* location) {_visit(location);};
};

struct Hiker : Visitor {
    Hiker(const string& name): Visitor{name} {};
    void visit(Mountain*);
}; 

struct Foodie : Visitor {
    Foodie(const string& name): Visitor{name} {};
    void visit(City*);
};

void demo_visitor();

#endif