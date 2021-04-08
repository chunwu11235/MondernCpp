#include "composite.h"
#include <iostream>
#include "string.h"
#include <vector>
#include <memory>

using namespace std;
struct Employee {
    static int total_employee;
    int id{};

    Employee() {
        id = ++total_employee;
    };

    virtual void work() const{
        cout << "employee " << id << " is working\n";
    };
};

int Employee::total_employee = 0;


struct Manager : public Employee {
    vector<const Employee*> team_members;
    void add_member(const Employee& employee ) {
        team_members.push_back(&employee);
    }

    void work() const override {
        cout << "--- manager " << id << " is working\n";
        for(auto& e : team_members) {
            e->work();
        }
    };
};


void demo_composite() {
    std::cout << "--- demo composite---\n";

    Manager ceo;
    Manager head_of_engineering;
    Manager team_lead;
    Employee sde1;
    Employee sde2;
    Employee seniorSde1;

    ceo.add_member(head_of_engineering);
    head_of_engineering.add_member(seniorSde1);
    head_of_engineering.add_member(team_lead);
    team_lead.add_member(sde1);
    team_lead.add_member(sde2);

    ceo.work();
}