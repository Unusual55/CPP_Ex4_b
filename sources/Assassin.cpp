#include "Assassin.hpp"
using coup::Action;
using coup::Player;
using coup::Game;
using coup::Assassin;
void Assassin::coup(Player &p) {
    turn_start();

    if (coins() < 3) {
        throw std::logic_error("Error: You need at least 3 coins in order to use coup");
    }

    if (p.getStatus() == TEMP_DEAD) {
        throw std::logic_error("Error: Cannot coup temporarily dead player");
    }

    if (p.getStatus() == DEAD) {
        throw std::logic_error("Error: What is dead may never die");
    }
    if(this->coins()<COUP_AMOUNT) {
        string str = "assassinate";
        this->decreaseCoins(3);

        p.setTempDead();
        game->addToSkip(p.getName());
        Action kill{str, false, this->getTurn()};
        actionToPlayers.insert({kill, &p});
        this->insertAction(kill, p);
        p.killPlayer();
        game->removePlayer(p.getName());
    }
    else{
        this->decreaseCoins(COUP_AMOUNT);
        p.killPlayer();
        game->removePlayer(p.getName());
        game->setRecent(name);
    }
    if(game->order[p.getName()]>game->order[name]) {
        turn_end();
    }
}


void Assassin::turn_start(){
    game->startGame();
    game->checkMoveInTurn(this->name);
    if(status == TEMP_DEAD || status == DEAD){
        throw std::logic_error("Error: Dead or temporarily dead players cannot make a move");
    }
    for(Action act: last_actions){
        string action = act.getAction();
        if(action == "assassinate" && !act.getBlocked()){
            Player p = *actionToPlayers[act];
            p.killPlayer();
            game->removePlayer(p.getName());
        }
    }
    last_actions.clear();
    actionToPlayers.clear();
}