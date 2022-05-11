#include "Player.hpp"
using namespace coup;

#pragma once
namespace coup {
    class Contessa : public Player {
    public:
        Contessa(Game &g, const string &name);

        void block(Player &p);
    };
};