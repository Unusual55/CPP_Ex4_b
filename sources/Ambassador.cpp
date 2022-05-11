//
// Created by ofri on 4/26/22.
//
#include "Ambassador.hpp"
using coup::Action;
using coup::Player;
using coup::Game;
using coup::Ambassador;


void Ambassador::transfer(Player &p1, Player &p2){
    this->turn_start();
    this->check_autoCoup();

    if(p1.coins()==0){
        throw std::logic_error("Error: Cannot transfer a coin from a player who have 0 coins");
    }

    p1.decreaseCoins(1);
    p2.increaseCoins(1);

    turn_end();
}

void Ambassador::block(Player &p1) const{
    vector<Action> actions = p1.getActions();
    string str1 = "steal1";
    string str2 = "steal2";
    bool check_flag = false;
    for(unsigned int i=0; i<actions.size();i++){
        if(actions[i].getAction()==str1 || actions[i].getAction()==str2){
            if(!validBlock(p1, actions[i])){
                throw std::logic_error("Error: Cannot use block, this block is invalid");
            }
            check_flag = true;
            Player &p2 = *p1.getMap()[actions[i]];
            if(actions[i].getAction()==str1){
                p1.decreaseCoins(STEAL_AMOUNT1);
                p2.increaseCoins(STEAL_AMOUNT1);
            }
            else {
                p1.decreaseCoins(STEAL_AMOUNT2);
                p2.increaseCoins(STEAL_AMOUNT2);
            }
            actions[i].set_blocked();
            p1.removeActionAt(i);
            break;
        }
    }
    if(!check_flag){
        throw std::logic_error("Error: The captain did not use steal");
    }
}
