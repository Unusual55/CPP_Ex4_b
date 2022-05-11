#include "Player.hpp"

#pragma once
namespace coup {
    class Captain : public Player {

        const unsigned int STEAL_AMOUNT1=1;
        const unsigned int STEAL_AMOUNT2=2;

        map<Action, coup::Player*> actionToPlayers;

    public:
        Captain(Game &g, const string &name): Player(name, "Captain", g){}

        void steal(Player &p1);

        void block(Player &p1) const;

        map<Action, coup::Player*> getMap() override{
            return this->actionToPlayers;
        }

        void turn_start() override;
    };
}