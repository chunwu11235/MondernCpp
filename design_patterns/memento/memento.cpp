#include "memento.hpp"
#include <iostream>
#include "string.h"
#include <memory>

using namespace std;


struct Position{
private:    
    struct Memento{
        const string _asset;
        const int _quantity;
        Memento(const string& _asset, int _quantity): _asset{_asset}, _quantity{_quantity} {};
    };

    string asset;
    int quantity;
public:
    Position(const string asset, int quantity): asset{asset}, quantity{quantity} {

    }
    
    const shared_ptr<Memento> createMemento() {
        return make_shared<Memento>(asset, quantity);
    }

    void restore(const shared_ptr<Memento>& m) {
        if(m != nullptr) {
            asset = m->_asset;
            quantity = m->_quantity;
        }
    }

    void buy(int q) {
        quantity += q;
    }

    void sell(int q) {
        if (q <= quantity) {
            quantity -= q;
        }
    }

    friend ostream& operator<<(ostream& os, const Position& p) {
        return os << p.asset << " " << p.quantity << endl;
    }
};



void demo_memento() {
    cout << "--- DEMO MEMENTO ---\n";    

    Position aapl{"APPL", 0};
    auto m1 = aapl.createMemento();
    aapl.buy(100);
    auto m2 = aapl.createMemento();
    cout << aapl << endl;

    aapl.restore(m1);
    cout << aapl << endl;

}