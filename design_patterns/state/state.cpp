#include "state.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

DiceGame::DiceGame(): _state{new NoSix{}} {};

void DiceGame::play() {
    int toss = rand() % 6 + 1;
    // cout << "Toss " << toss << endl;
    _state->transit(*this, toss);
}

bool DiceGame::stop() const{
    return _state->isEnd;
}

void NoSix::transit(DiceGame& dice_game, int trigger) {
    if(trigger == 6) {
        dice_game.set_state(new OneSix());
        delete this;
    }
}

void OneSix::transit(DiceGame& dice_game, int trigger) {
    if(trigger == 6) {
        dice_game.set_state(new TwoSix());
    }else{
        dice_game.set_state(new NoSix());
    }
    delete this;
}

TwoSix::TwoSix() {
    isEnd = true;
};

void TwoSix::transit(DiceGame& dice_game, int trigger) {}

void demo_state() {
    cout << "--- DEMO STATE ---\n";

    int n_simu{500};
    int count{0};

    // Monte-Carlo simulation
    for(int i = 0; i < n_simu; ++i) {
        cout << "--- New Game ---\n";
        DiceGame game{};
        int _count{};
        while(!game.stop()) {
            game.play();
            ++_count;
        }
        cout << _count << " toss" << endl;
        cout << "--- End Game ---\n";
        count += _count;

    }

    cout << (float) count/n_simu << endl; // should be close to 42


    cout << "--- DEMO END --- \n";
}