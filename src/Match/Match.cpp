#include "Match.hpp"

using namespace Engine;
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
void Match::setPitch(UniquePtr<Sprite> in_pitch) { pitch = std::move(in_pitch); }
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
