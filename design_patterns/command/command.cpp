#include "command.hpp"
#include <iostream>
#include "string.h"

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
        }
        cout << "Execution succeed\n";
    }

    void undo() override {
        if(!isExecuted) return;
        bool success = asset.sell(quantity);
        if (!success) {
            cout << "Failed to undo" << endl;
        }
        cout << "Undo succeed\n";
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

void demo_command() {
    cout << "--- DEMO COMMAND ---\n";

    Asset appl("APPL", 10);
    Buy buy100(appl, 100);
    buy100.execute();
}