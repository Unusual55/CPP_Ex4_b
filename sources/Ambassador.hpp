#include "Player.hpp"
using namespace coup;

namespace coup {
    class Ambassador : public Player {
        const unsigned int STEAL_AMOUNT1=1;
        const unsigned int STEAL_AMOUNT2=2;
    public:
        Ambassador(Game &g, const string &name): Player(name, "Ambassador", g){}

        void transfer(Player &p1, Player &p2);

        void block(Player &p1) const;
    };
}