#include "singleton.hpp"
#include <iostream>
#include <memory>

using namespace std;
// lazy initialization, NOT THREAD-SAFE 
class Singleton_Lazy{
private:
    static int count;
    static shared_ptr<Singleton_Lazy> _instance; // nullptr by default

    Singleton_Lazy() {
        cout << "--- Singleton_Lazy()---\n"; // should only be called onces
        ++Singleton_Lazy::count;
    };

    Singleton_Lazy(const Singleton_Lazy& other) = delete; // no copy is allowed
    Singleton_Lazy& operator= (const Singleton_Lazy& other) = delete; // no copy assignment

public:
    void printInstanceCount() const {
        cout << "instance count: " << Singleton_Lazy::count << "\n"; // should always be 1
    }

    static shared_ptr<Singleton_Lazy> getInstance() {
        if(_instance == nullptr) {
            _instance.reset(new Singleton_Lazy());
        }
        return _instance;
    }    
};

int Singleton_Lazy::count = 0;
shared_ptr<Singleton_Lazy> Singleton_Lazy::_instance{nullptr};

void demo_singleton() {
    cout << "--- Demo Singleton\n";

    auto s1 = Singleton_Lazy::getInstance();
    auto s2 = Singleton_Lazy::getInstance();

    s1->printInstanceCount(); // 1
    s2->printInstanceCount(); // 1
}