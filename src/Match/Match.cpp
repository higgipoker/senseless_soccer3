#include "Match.hpp"
//
//
//
Match::Match() {}
//
//
//
void Match::setBall(Ball& in_ball) { ball = &in_ball; }
//
//
//
Ball& Match::getBall() { return *ball; }
