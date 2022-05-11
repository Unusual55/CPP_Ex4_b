#include <string>
using std::string;

using namespace std;
namespace coup {
    class Action {
        string action="None";
        bool blocked=false;
        unsigned int turn=0;
    public:

        Action()= default;


        Action(const std::string &name, bool b, unsigned int turn);

        void set_blocked(){
            blocked = true;
        }

        string getAction(){
            return this->action;
        }

        unsigned int getTurn() const{
            return this->turn;
        }

        bool getBlocked() const{
            return blocked;
        }

        bool operator<(const Action &act) const{
            return action<act.action;
        }

    };
}

