//
// Created by ofri on 4/26/22.
//
#include "Game.hpp"
using namespace std;
using coup::Game;

vector<string> Game::players() {
    return this->active_players;
}

string Game::winner() {
    if(!isEnded()) {
        throw std::logic_error("Error: winner() cannot be used while the game is active");
    }
    return active_players[0];
}

bool Game::isEnded() {
    return active_players.size()==1 && started;
}

void Game::addPlayer(const string &name) {
    if(this->started){
        throw std::logic_error("Error: Cannot add players after the game begun");
    }
    if(this->active_players.size()>=MAX_PLAYERS) {
        throw std::logic_error("Error: The game already has maximal amount of players");
    }
    this->active_players.push_back(name);
    this->order[name]=(int)active_players.size();
}

void Game::removePlayer(const string &name) {
    for(unsigned int i=0; i< active_players.size(); i++) {
        if(active_players[i]==name) {
            active_players.erase(active_players.begin()+i);
            return;
        }
    }
//    throw std::invalid_argument("Error: No such player");
}

/**
 * Check if there are 2-6 players, return true if there are, else false
 * @return
 */
bool Game::canStart() {
    return active_players.size()>=MIN_PLAYERS && active_players.size()<=MAX_PLAYERS && !started;
}


/**
 * start the game if there are 2-6 players, else throw exception
 * @return
 */
void Game::startGame() {
    if(started) {
        return;
    }
    if (canStart()) {
        this->started = true;
    }
    else {
        throw std::logic_error("Error: Not enough players to start the game");
    }
}

void Game::checkMoveInTurn(const string &name){
    if(active_players[turn_index]!=name) {
        throw std::logic_error("Error: This action cannot be used during other player turn");
    }
}
