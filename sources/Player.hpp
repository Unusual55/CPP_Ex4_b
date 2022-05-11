#include <string>
#include <vector>
#include <map>
#include "Game.hpp"
#include "Action.hpp"

#define ALIVE 1
#define TEMP_DEAD 0
#define DEAD -1
#pragma once

using namespace std;
using std::string;
namespace coup {
    class Player {
    protected:
        unsigned int cash = 0;
        string character;
        unsigned int turn=0;
        const unsigned int COUP_AMOUNT = 7;
        Game *game{};
        int status = ALIVE;
        string name;
        vector <Action> last_actions;
    public:

        Player()= default;

        Player(Game &g, const string &name);

        Player(const string &name, const string &role, Game &g): name(name), character(role), game(&g){
            game->addPlayer(name);
        }

        void income();

        void foreign_aid();

        virtual void coup(Player &p);

        string role() {
            return this->character;
        }

        unsigned int getTurn() const{
            return this->turn;
        }

        unsigned int coins() const {
            return this->cash;
        }

        string getName() {
            return this->name;
        }

        void killPlayer(){
            this->status = DEAD;
        }

        void setTempDead(){
            this->status = TEMP_DEAD;
        }

        virtual void turn_start();

        void turn_end(){
            turn++;
            game->nextTurn();
        }

        void check_autoCoup() const{
            if(cash>=10){
                throw std::logic_error("Error: You have 10 or more coins, you have to use coup this turn");
            }
        }

        void increaseCoins(unsigned int count){
            this->cash+=count;
        }

        void decreaseCoins(unsigned int count){
            this->cash-=count;
        }

        static bool validBlock(Player &p, Action &act){
            if(act.getBlocked()){
                return false;
            }
            bool ret= false;
            if(p.game->turn()==p.getName()){
                //block in his turn
                if(act.getTurn()==p.getTurn()){
                    ret= true;
                }
                else if(p.getTurn()-act.getTurn()==1){
                    ret= false;
                }
                return ret;
            }
            return true;
        }

        vector<Action> getActions(){
           return this->last_actions;
        }

        int getStatus() const{
            return this->status;
        }

        void insertAction(Action &act, Player &p){
            last_actions.push_back(act);
        }

        void setAlive(){
            if(status == DEAD) {
                this->status = ALIVE;
            }
        }

        virtual map<Action, Player *> getMap(){
            throw std::logic_error("No implementation");
        }

        void removeActionAt(unsigned int index){
            last_actions.erase(last_actions.begin()+index);
        }
    };
}