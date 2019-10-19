#include "Match.hpp"
//
//
//
Match::Match() {}
//
//
//
void Match::setBall(std::unique_ptr<Ball> in_ball) {
  ball = std::move(in_ball);
}
//
//
//
Ball& Match::getBall() { return *ball; }
