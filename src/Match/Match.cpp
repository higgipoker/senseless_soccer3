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
  ball->update();
  home_team->update();
  away_team->update();

  // keep the ball in the pitch
  auto pitchrect = static_cast<Pitch*>(pitch.get())->dimensions.bounds;

  if (ball->movable.position.x < pitchrect.getPosition().x) {
    ball->movable.velocity.x = -ball->movable.velocity.x;
  }
  if (ball->movable.position.x >
      pitchrect.getPosition().x + pitchrect.getSize().x) {
    ball->movable.velocity.x = -ball->movable.velocity.x;
  }

  if (ball->movable.position.y < pitchrect.getPosition().y) {
    ball->movable.velocity.y = -ball->movable.velocity.y;
  }
  if (ball->movable.position.y >
      pitchrect.getPosition().y + pitchrect.getSize().y) {
    ball->movable.velocity.y = -ball->movable.velocity.y;
  }
}
//
//
//
void Match::setPitch(UniquePtr<Sprite> in_pitch) {
  pitch = std::move(in_pitch);
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
