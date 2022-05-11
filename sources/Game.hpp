#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#pragma once
using namespace std;
using std::string;

namespace coup {
    class Game {
        string recent;
        const unsigned int MIN_PLAYERS = 2;
        const unsigned int MAX_PLAYERS = 6;
        vector <string> active_players;
        unsigned int turn_index = 0;
        bool ended = false;
        bool started = false;
        unordered_set<string> skip_players;

    public:
        unordered_map<string, int> order;

        Game() { }

        ~Game() { }

        void nextTurn() {
            if(turn_index==active_players.size()){
                recent = active_players[turn_index-1];
                turn_index %= active_players.size();
            }
            else {
                recent = active_players[turn_index];
                turn_index += 1;
                turn_index %= active_players.size();
            }

            if(recent==active_players[turn_index]){
                turn_index += 1;
                turn_index %= active_players.size();
            }
        }


        string turn() {
            if(active_players.size()>0){
                return active_players[turn_index];
            }
            return "No players entered yet";
        }

        vector<string> players();

        string winner();

        bool isEnded();

        void addPlayer(const string &name);

        void removePlayer(const string &name);

        /**
         * Check if there are 2-6 players, return true if there are, else false
         * @return
         */
        bool canStart();


        /**
         * start the game if there are 2-6 players, else throw exception
         * @return
         */
        void startGame();

        bool isStarted() const{
            return this->started;
        }

        void checkMoveInTurn(const string &name);

        void addToSkip(const string &name){
            skip_players.insert(name);
        }

        void removeFromSkip(const string &name){
            skip_players.erase(name);
        }

        void revivePlayer(const string &name){
            if(!order.at(name)){
                throw std::logic_error("Error: no player found");
            }
            if(order[name]==1){
                active_players.insert(active_players.begin() + 0, name);
            }
            else if(order[name]==order.size()){
                active_players.push_back(name);
            }
            else {
                unsigned int i=0;
                while(order[name]>order[active_players[i]]){
                    i++;
                }
                active_players.insert(active_players.begin()+i, 1, name);
            }
        }

        void setRecent(string &name){
            recent=name;
            turn_index %= active_players.size();
        }

        string getRecent(){
            return recent;
        }
    };
}