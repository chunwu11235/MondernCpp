#include "observer.hpp"
#include <iostream>
#include <unordered_set>
#include <memory>
#include "string.h"
#include <sstream>

using namespace std;

template<typename T>
struct Observer;

// aka pulisher
template<typename T>
struct Observable{
    virtual void subscribe(const shared_ptr<Observer<T>>& observer) {
        _observers.insert(observer);   
    };
    virtual void unsubscribe(const shared_ptr<Observer<T>>& observer) {
        _observers.erase(observer);
    }

    virtual string to_str() const = 0;

protected:
    unordered_set<shared_ptr<Observer<T>>> _observers{};
    virtual void notify() {
        for(auto obs : _observers) {
            obs->on_change(*this);
        }
    };
};

// aka subscriber
template<typename T>
struct Observer {
    virtual void on_change(const Observable<T>& observable) {
        cout << "Observer " << this << " has a update: " 
        << observable.to_str() << endl;
    };
};

struct Bond : public Observable<Bond> {
    Bond(int price): price{price} {};
    int get_price() const {
        return price;
    }

    void set_price(int price) {
        if(this->price != price) {
            this->price = price;
            this->notify();
        }
    }

    string to_str() const override {
        ostringstream oss;
        oss << "Bond " << this << " with price " << this->get_price() ;
        return oss.str();
    }

private:
    int price{};
};

void demo_observer() {
    cout << "--- Demo Observer ---\n";

    Bond bond1{100};
    auto investor1 = make_shared<Observer<Bond>>();
    auto investor2 = make_shared<Observer<Bond>>();

    bond1.unsubscribe(investor1);

    bond1.set_price(19);

    cout << "--- subscribe " << investor1 << endl;
    bond1.subscribe(investor1);
    bond1.set_price(203); // only 1 update for invecstor 1

    cout << "--- unsubscribe " << investor2 << endl;
    bond1.subscribe(investor2);
    bond1.set_price(255); // should see 2 updates

    cout << "--- unsubscribe " << investor1 << endl;
    bond1.unsubscribe(investor1);
    bond1.set_price(255); // no update since the price doesn't change
    bond1.set_price(270);

    cout << "---Program End---\n";
}