#include "mediator.hpp"
#include <iostream>
#include "string.h"
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

template<typename T>
struct Mediator {
    unordered_set<T*> _members{};

    void register_member(T& member) {
        _members.insert(&member);
        cout << "---" << member.name << " Joined ---\n";
    }

    void send(const string& from, const string& to, const string& message) {
        for(auto& member : _members) {
            if(member->name == to) {
                member->receive(from , message);
            }
        }
    }
};


struct Person{
    string name{};
    Mediator<Person> * mediator{nullptr};
    
    Person(string&& name):name{move(name)} {};

    void join(Mediator<Person>& mediator) {
        this->mediator = &mediator;
        this->mediator->register_member(*this);
    }

    void send(const string& to, const string& message) {
        mediator->send(name, to, message);
    }

    void receive(const string& from, const string& message) {
        cout << from <<  " to " << name << ": " << message << endl;
    }
};


void demo_mediator() {
    cout << "--- DEMO MEDIATOR --- \n";
    Mediator<Person> chatroom{};

    Person Andy{"Andy"};
    Person Bob{"Bob"};
    
    Andy.join(chatroom);
    Andy.send("Bob", "What's up!"); // Bob is not in the chat room

    Bob.join(chatroom);
    Andy.send("Bob", "What's up, bro!");
    Bob.send("Andy", "Yee-Ha!");


}