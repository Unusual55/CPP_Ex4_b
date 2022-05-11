#include "Captain.hpp"
using coup::Action;
using coup::Player;
using coup::Game;
using coup::Captain;

void Captain::steal(Player &p1){
    turn_start();
    check_autoCoup();

    if(p1.getStatus() == TEMP_DEAD){
        throw std::logic_error("Error: You cannot steal from temporarily dead players");
    }

    if(p1.getStatus() == DEAD){
        throw std::logic_error("Error: You cannot still from dead players");
    }

    string str1 = "steal1";
    string str2 = "steal2";

    if(p1.coins()==1){
        Action act{str1, false, getTurn()};
        insertAction(act, p1);
        actionToPlayers.insert({act, &p1});
        p1.decreaseCoins(STEAL_AMOUNT1);
        increaseCoins(STEAL_AMOUNT1);
    }
    else if(p1.coins()>=2){
        Action act{str2, false, getTurn()};
        insertAction(act, p1);
        actionToPlayers.insert({act, &p1});
        p1.decreaseCoins(STEAL_AMOUNT2);
        increaseCoins(STEAL_AMOUNT2);
    }

    turn_end();
}

void Captain::block(Player &p1) const{
    //Check if the player is a captain
    if(p1.role()!="Captain"){
        throw std::logic_error("Captain can only block another captain");
    }
    string str1 = "steal1";
    string str2 = "steal2";
    vector<Action> actions = p1.getActions();
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

void Captain::turn_start(){
    game->startGame();
    game->checkMoveInTurn(this->name);
    if(status == TEMP_DEAD || status == DEAD){
        throw std::logic_error("Error: Dead or temporarily dead players cannot make a move");
    }
    last_actions.clear();
    actionToPlayers.clear();
}
