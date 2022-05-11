//
// Created by ofri on 4/25/22.
#include "Player.hpp"
using coup::Player;
using coup::Game;
using coup::Action;
using std::string;

Player::Player(Game &g, const string &name){
    this->name = name;
    this->game = &g;
}

void Player::income(){
    turn_start();
    check_autoCoup();
    this->cash++;
    turn_end();
}

void Player::foreign_aid(){
    turn_start();
    check_autoCoup();

    string identifier ="foreign_aid";
    Action for_aid=Action(identifier, false, this->turn);
    last_actions.push_back(for_aid);
    this->cash+=2;

    turn_end();
}

void Player::coup(Player &p) {
    turn_start();

    if (p.status == DEAD || p.status == TEMP_DEAD) {
        throw std::logic_error("Error: what is dead may never die!");
    }

    if (coins() < COUP_AMOUNT) {
        throw std::logic_error("Error: You need at least 7 coins in order to use coup");
    }
    cash -= COUP_AMOUNT;
    p.killPlayer();
    game->removePlayer(p.getName());

    if (game->order[p.getName()] > game->order[name]) {
        turn_end();
    } else {
        if(game->turn()==name){
            turn_end();
        }
        else{game->setRecent(name);}
    }
}

void Player::turn_start(){
    game->startGame();
    game->checkMoveInTurn(this->name);
    if(status == TEMP_DEAD || status == DEAD){
        throw std::logic_error("Error: Dead or temporarily dead players cannot make a move");
    }
    for(Action act: last_actions){
        string action = act.getAction();
    }
    last_actions.clear();
}
