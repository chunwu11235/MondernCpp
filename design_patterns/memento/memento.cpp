#include "memento.hpp"
#include <iostream>
#include "string.h"
#include <memory>
#include <vector>

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
    vector<const shared_ptr<Memento>> snapshots{};
    int current{-1};

    void take_a_snapshot() {
        snapshots.emplace_back(createMemento());
        ++current;
    }

public:
    Position(const string asset, int quantity): asset{asset}, quantity{quantity} {
        take_a_snapshot();
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
        take_a_snapshot();
    }

    void sell(int q) {
        if (q <= quantity) {
            quantity -= q;
            take_a_snapshot();

        }else{
            cout << "No enough quantity to sell\n";
        }
    }

    void undo() {
        if(current > 0) {
            auto m = snapshots.at(--current);
            restore(m);
        }else{
            cout << "Unable to undo\n";
        }
    }

    void redo() {
        if(current + 1 < snapshots.size()) {
            auto m = snapshots.at(++current);
            restore(m);
        }else{
            cout << "Unable to redo\n";
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

    cout << "--- Undo/Redo --- \n";

    Position ibm{"IBM", 0};
    ibm.buy(20);
    ibm.buy(40);
    ibm.buy(100);
    cout << ibm << endl; // 160

    ibm.undo();
    cout << ibm << endl; // 60

    ibm.undo();
    cout << ibm << endl; // 20

    ibm.redo();
    cout << ibm << endl; // 60

    ibm.redo();
    cout << ibm << endl; // 160

    ibm.redo(); // unable to redo
    cout << ibm << endl; // 160

    cout << "--- PROGRAM END ---\n";
}