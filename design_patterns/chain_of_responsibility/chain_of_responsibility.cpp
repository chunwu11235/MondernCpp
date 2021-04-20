#include "chain_of_responsibility.hpp"
#include <iostream>
#include "string.h"

using namespace std;

struct Project {
    string name;
    int tech_level;
    int management_level;
    Project(const string& name, int tech_level, int management_level):
        name{name}, tech_level{tech_level}, management_level{management_level} {};
};


struct Worker{
    string name;
    Worker* const supervisor;
    int tech_level;
    int management_level;
    
    Worker(const string& name, int tech_level, int management_level, Worker* const worker):
        name{name}, tech_level{tech_level}, management_level{management_level}, supervisor{worker}
        {};
    virtual void handle(Project& project) {
        if(project.management_level <= management_level && project.tech_level <= tech_level) {
            cout << "Project: " << project.name << " is handled by " << name << endl;
            return;
        }

        if(supervisor != nullptr) {
            // escalate
            return supervisor->handle(project);
        }

        cout << "No one is able to handle this project " << project.name << endl;
    }
};

void demo_chain_of_responsibility() {
    cout << "---DEMO CHAIN_OF_RESPONSIBILITY---\n";

    // chian of responsibility
    Worker ceo{"CEO", 3, 10, nullptr};
    Worker cto{"CTO", 8, 8, &ceo};
    Worker tech_fellow{"Tech Fellow", 10, 4, &cto};
    Worker manager{"Manager", 5, 6, &tech_fellow};
    Worker sde{"Developer007", 7, 2, &manager};
    Worker intern{"intern", 0, 0, &sde};

    Project p1{"Turn on a computer", 0, 0};
    Project p2{"Build a web", 5, 5};
    Project p3{"Build Self-Driving Car", 10, 7};
    Project p4{"Talk to the media", 3, 10};


    intern.handle(p1);
    intern.handle(p2);
    intern.handle(p3);
    intern.handle(p4);

}