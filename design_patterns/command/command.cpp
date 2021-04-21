#include "command.hpp"
#include <iostream>
#include "string.h"
#include <vector>

using namespace std;
struct Asset{
    const string asset_name;
    int quantity{};

    Asset(const string& name, int quantity): asset_name{name}, quantity{quantity} {};

    bool buy(int q) {
        quantity += q;
        cout << "Buy " << q << " of " << asset_name << endl;
        return true;
    }

    bool sell(int q) {
        if(q <= quantity) {
            quantity -= q;
            cout << "Sell " << q << " of " << asset_name << endl;
            return true;
        }
        cout << "Not enough quantity of " << asset_name << " to sell" << endl;
        return false;
    }

    int get_quantity() {
        return quantity;
    }
};

struct Command {
    virtual void execute() = 0;
    virtual void undo() = 0;
    Command() {
        // cout << "Command()\n";
    }
    virtual ~Command() {
        cout << "~Command\n";
    };
protected:
    bool isExecuted{false};
    
};

struct Buy : Command {
private:
    Asset& asset;
    int quantity{};
public:
    Buy(Asset& asset, int quantity): asset{asset}, quantity{quantity} {};
    void execute() override {
        isExecuted = asset.buy(quantity);
        if(!isExecuted) {
            cout << "Failed to execute\n";
        }else{
            cout << "Execution succeed\n";
        }
    }

    void undo() override {
        if(!isExecuted) return;
        bool success = asset.sell(quantity);
        if (!success) {
            cout << "Failed to undo" << endl;
        }else{
            cout << "Undo succeed\n";
        }
    }
};

struct Sell : Command {
private:
    Asset& asset;
    int quantity{};
public:
    Sell(Asset& asset, int quantity): asset{asset}, quantity{quantity} {};
    void execute() override {
        isExecuted = asset.sell(quantity);
        if(!isExecuted) {
            cout << "Failed to execute\n";
        }else{
            cout << "Execution succeed\n";
        }
    }

    void undo() override {
        if(!isExecuted) return;
        bool success = asset.buy(quantity);
        if (!success) {
            cout << "Failed to undo" << endl;
        }else{
            cout << "Undo succeed\n";
        }
        
    }
};

struct DumpAll : Command {
private:
    Asset& asset;
    int quantity{};
public:
    DumpAll(Asset& asset): asset{asset} {};
    void execute() override {
        cout << "Dumping all position of " << asset.asset_name << endl;
        int q_temp = asset.get_quantity();
        isExecuted = asset.sell(q_temp);
        if(!isExecuted) {
            cout << "Failed to execute\n";
        }else{
            quantity = q_temp;
            cout << "Execution succeed\n";
        }
    }

    void undo() override {
        if(!isExecuted) return;
        bool success = asset.buy(quantity);
        if (!success) {
            cout << "Failed to undo" << endl;
        }else{
            cout << "Undo succeed\n";
        }
    }
};

struct Trader{
private:
    vector<unique_ptr<Command>> order_history{};
public:    
    void take_order(unique_ptr<Command>&& order) {
        order->execute();
        order_history.push_back(move(order));
    }

    void undo_trades() {
        cout << "--- Undo Trading --- \n";
        while(!order_history.empty()) {
            order_history.back()->undo();
            order_history.pop_back();
        }
    }
};

void demo_command() {
    cout << "--- DEMO COMMAND ---\n";

    Asset appl("APPL", 10);
    Buy buy100(appl, 100);
    buy100.execute();
    DumpAll dumpAll(appl);
    dumpAll.execute();
    buy100.undo(); // failed
    dumpAll.undo();
    buy100.undo();
    cout << appl.get_quantity() << endl; // 10


    cout << "--- Trader Class ---\n";

    Asset goog("GOOG", 300);
    Trader trader{};
    trader.take_order(make_unique<Buy>(goog, 101));
    trader.take_order(make_unique<Buy>(goog, 21));
    trader.take_order(make_unique<DumpAll>(goog));
    trader.take_order(make_unique<Buy>(goog, 211));

    trader.undo_trades();

    cout << "--- Program End ---\n";
    
    

}