#include "Duke.hpp"
using coup::Action;
using coup::Player;
using coup::Game;
using coup::Duke;

Duke::Duke(Game &g, const string &name): Player(name, "Duke", g){}

void Duke::tax(){
    turn_start();
    check_autoCoup();

    increaseCoins(3);
    turn_end();
}

void Duke::block(Player &p) const {
    vector <Action> actions = p.getActions();
    bool check_flag = false;
    for (unsigned int i=0; i<actions.size();i++) {
        if (actions[i].getAction() == "foreign_aid") {
            if (!validBlock(p, actions[i])) {
                throw std::logic_error("Error: Cannot use block, this block is invalid");
            }
            p.decreaseCoins(AID_AMOUNT);
            actions[i].set_blocked();
            p.removeActionAt(i);
            return;
        }
    }
    if(!check_flag) {
        throw std::logic_error("Error: Cannot block the player since he did not use foreign_aid");
    }
}