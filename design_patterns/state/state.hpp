#pragma once
#ifndef DESIGN_PATTERNS_STATE
#define DESIGN_PATTERNS_STATE

struct State;

// keep tossing dice until you get 2 consecutive 6
struct DiceGame{
    State* _state{nullptr};
    DiceGame();
    void set_state(State* s) {
        _state = s;
    };
    void play();
    bool stop() const;
};

struct State{
    bool isEnd{false};
    virtual void transit(DiceGame& dice_game, int trigger) = 0;
};

struct NoSix : State {
    virtual void transit(DiceGame& dice_game, int trigger) override;
};

struct OneSix : State {
    virtual void transit(DiceGame& dice_game, int trigger) override;
};

struct TwoSix : State {
    TwoSix();
    virtual void transit(DiceGame& dice_game, int trigger) override;
}; 



void demo_state();

#endif