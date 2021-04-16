#include "singleton.hpp"
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <vector>
#include <typeinfo>

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
    void printInstanceCount() const{
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


template<typename T>
void run_threads(int n) {
    cout << "--- test with multi-threading " << typeid(T).name() << endl;

    vector<thread> threads;
    for (int i = 0; i < n; ++i)
    {
        threads.emplace_back([i]()
        {
            // cout << "creating thread " << i << endl;
            auto s = T::getInstance();
            s->printInstanceCount();
        });
    }

    for_each(threads.begin(), threads.end(), [] (thread& t){ t.join(); });
};

void demo_singleton() {
    cout << "--- Demo Singleton\n";

    // NOT THREAD-SAFE 
    run_threads<Singleton_Lazy>(30);

}