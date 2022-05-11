#include "Player.hpp"
using namespace coup;

namespace coup {
    class Assassin : public Player {


    public:

        map<Action, coup::Player *> actionToPlayers;

        Assassin(Game &g, const string &name): Player(name, "Assassin", g){}

        ~Assassin()= default;

        void coup(Player &p) override;

        void turn_start() override;

        map<Action, coup::Player *> getMap() override{
            return this->actionToPlayers;
        }

    };
}