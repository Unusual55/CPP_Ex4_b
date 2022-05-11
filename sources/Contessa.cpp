#include "Contessa.hpp"
using coup::Action;
using coup::Player;
using coup::Game;
using coup::Contessa;
Contessa::Contessa(Game &g, const string &name): Player(name, "Contessa", g){}

void Contessa::block(Player &p) {
    if(p.role()!="Assassin"){
        throw std::logic_error("Error: Contessa can only block assassins");
    }
    vector <Action> actions = p.getActions();
    bool check_flag = false;
    for (unsigned int i = 0; i < actions.size(); i++) {
        if (actions[i].getAction() == "assassinate") {
            if (!validBlock(p, actions[i])) {
                throw std::logic_error("Error: Cannot use block, this block is invalid");
            }
            Player &p1 = *p.getMap()[actions[i]];
            game->removeFromSkip(p1.getName());
            p1.setAlive();
            actions[i].set_blocked();
            p.removeActionAt(i);
            game->revivePlayer(p1.getName());

            if(game->getRecent()==game->turn()){
                game->nextTurn();
            }
            if(game->order[name]<game->order[p1.getName()]&&game->turn()!=name){
                game->nextTurn();
            }
            return;
        }
    }
    if(!check_flag) {
        throw std::logic_error("Error: The assassin did not use coup");
    }
}
