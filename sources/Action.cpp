//
// Created by ofri on 4/24/22.
//
#include "Action.hpp"
using coup::Action;

Action::Action(const string &name, bool b, unsigned int turn): action(name), blocked(b), turn(turn){}

