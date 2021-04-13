#include "template_method.h"
#include <iostream>

struct Project{
    void start() {
        std::cout << "--- Project Starts ---\n";
        phase1();
        phase2();
        phase3();
        phase4();
        std::cout << "--- Project Ends ---\n";
    };
protected:
    virtual void phase1() = 0;
    virtual void phase2() = 0;
    virtual void phase3() = 0;
    virtual void phase4() = 0;
};

struct SofwareDevelopment : Project {
private: 
    void phase1() override {
        std::cout << "Planning and Designing\n";
    }

    void phase2() override {
        std::cout << "Developing and Testing\n";
    }

    void phase3() override {
        std::cout << "More Testing\n";
    }

    void phase4() override {
        std::cout << "Releasing and Improving Product\n";
    }
};

struct DataAnalysis : Project {
private:    
    void phase1() override {
        std::cout << "Planning and Formulating Business Problems\n";
    }

    void phase2() override {
        std::cout << "Collecting Data and Data-Preprocessing\n";
    }

    void phase3() override {
        std::cout << "Modelling and Analyzing Data\n";
    }

    void phase4() override {
        std::cout << "Generating Business Insights\n";
    }
};




void demo_template_method() {
    std::cout << "--- Demo Template Method\n";

    DataAnalysis da;
    da.start();

    SofwareDevelopment sd;
    sd.start();
}