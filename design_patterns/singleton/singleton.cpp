#include "singleton.hpp"
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <vector>
#include <typeinfo>
#include "string.h"

using namespace std;

// lazy initialization, NOT THREAD-SAFE 
class Singleton_Lazy{
private:
    static int count;
    static shared_ptr<Singleton_Lazy> _instance; // nullptr by default
    // static mutex mtx;
    
    Singleton_Lazy(const Singleton_Lazy& other) = delete; // no copy is allowed
    Singleton_Lazy& operator= (const Singleton_Lazy& other) = delete; // no copy assignment

    Singleton_Lazy() {
        cout << "Singleton_Lazy()\n"; // should only be called onces
        ++Singleton_Lazy::count;   
        if(Singleton_Lazy::count > 1) {
            cout << "Multiple instances\n";
        }     
    }

public:
    ~Singleton_Lazy() {
        cout << "~Singleton_Lazy()\n";
    }
    
    void printInstanceCount() const{
        cout << typeid(*this).name() << " instance count: " << count << "\n"; // should always be 1
    }

    // not thread safe
    static shared_ptr<Singleton_Lazy> getInstance() {
        if(_instance == nullptr) {
            _instance.reset(new Singleton_Lazy());
        }
        return _instance;
    } 
};

int Singleton_Lazy::count{0};
shared_ptr<Singleton_Lazy> Singleton_Lazy::_instance;



class Singleton_Lazy_With_Lock{
private:
    static mutex mtx;
    static int count;
    static shared_ptr<Singleton_Lazy_With_Lock> _instance; // nullptr by default
    // static mutex mtx;
    
    Singleton_Lazy_With_Lock(const Singleton_Lazy_With_Lock& other) = delete; // no copy is allowed
    Singleton_Lazy_With_Lock& operator= (const Singleton_Lazy_With_Lock& other) = delete; // no copy assignment

    Singleton_Lazy_With_Lock() {
        cout << "Singleton_Lazy_With_Lock()\n"; // should only be called onces
        ++Singleton_Lazy_With_Lock::count;
        if(Singleton_Lazy_With_Lock::count > 1) {
            cout << "Multiple instances\n";
        }   
    }

public:
    ~Singleton_Lazy_With_Lock() {
        cout << "~Singleton_Lazy_With_Lock()\n";
    }
    void printInstanceCount() const{
        cout << typeid(*this).name() << " instance count: " << count << "\n"; // should always be 1
    }

    // double checked locking, thread safe
    static shared_ptr<Singleton_Lazy_With_Lock> getInstance() {
        if(_instance == nullptr) {
            mtx.lock();
            if(_instance == nullptr) {
                _instance.reset(new Singleton_Lazy_With_Lock());
            }
        }
        return _instance;
    } 
};

int Singleton_Lazy_With_Lock::count{0};
shared_ptr<Singleton_Lazy_With_Lock> Singleton_Lazy_With_Lock::_instance;
mutex Singleton_Lazy_With_Lock::mtx;


// should use this one, thread safe
struct Singleton {
private:
    static int count;
    Singleton() {
        cout << "Singleton()\n";
        ++ Singleton::count;
        if(Singleton::count > 1) {
            cout << "Multiple instances!\n";
        }
    }

    Singleton(const Singleton& other) = delete;
    Singleton& operator= (const Singleton& other) = delete;

public:
    void printInstanceCount() const{
        cout << typeid(*this).name() << " instance count: " << count << "\n"; // should always be 1
    }
    static Singleton* getInstance() {
        static Singleton _instance;
        return &_instance;
    }    
};

int Singleton::count{0};


template<typename T>
void run_threads(int n) {
    cout << "--- test with multi-threading " << typeid(T).name() << endl;
    vector<thread> threads;

    for (int i = 0; i < n; ++i)
    {
        threads.emplace_back([i]()
        {
            auto&& s = T::getInstance();
            s->printInstanceCount();
        });
    }
    for_each(threads.begin(), threads.end(), [] (thread& t){ t.join(); });
};

void demo_singleton() {
    cout << "--- Demo Singleton\n";

    // NOT THREAD-SAFE 
    run_threads<Singleton_Lazy>(10); // you will get at least 2 instance with high probability
    cin.get();

    cout << "--- Double Checked Locking\n";
    run_threads<Singleton_Lazy_With_Lock>(10); // thread safe

    cin.get();

    cout << "-- Use Static Local Variable\n";
    run_threads<Singleton>(10);

    cout << "--- Program End ---\n";
}