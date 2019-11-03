#include "Match.hpp"
//
//
//
Match::Match() {}
//
//
//
void Match::update() {
  home_team->update();
  away_team->update();
}
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
//
//
//
void Match::addTeams(UniquePtr<Team> in_home_team,
                     UniquePtr<Team> in_away_team) {
  home_team = std::move(in_home_team);
  away_team = std::move(in_away_team);
}
