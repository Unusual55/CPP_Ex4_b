#include "Player.hpp"
#pragma once

namespace coup {
    class Duke : public Player {
    public:
        const unsigned int AID_AMOUNT = 2;

        Duke(Game &g, const string &name);

        void tax();

        void block(Player &p) const;
    };
}