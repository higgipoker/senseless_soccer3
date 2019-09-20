#include "Player.hpp"

#include "Engine/Compass.hpp"
#include "Match/Match.hpp"

Match* Player::match = nullptr;

const int SHADOW_OFFSET_X = 1;
const int SHADOW_OFFSET_Y = 4;
//
//
//
Player::Player(PlayerSprite* in_sprite, PlayerShadowSprite* in_shadow)
    : state_stand(*this), state_run(*this), current_state(&state_stand) {
  movable = &player_movable;

  // base entity members
  sprite = in_sprite;
  shadow = in_shadow;

  // player members
  player_sprite = in_sprite;
  player_shadow = in_shadow;
}
//
//
//
void Player::update() {
  // state machine
  current_state->step();
  if (current_state->stateOver()) {
    current_state->end();
    current_state->changeToNextState();
    current_state->start();
  }

  sprite->animate();
  shadow->setPosition(sprite->getPosition());
  shadow->move(SHADOW_OFFSET_X, SHADOW_OFFSET_Y);
  shadow->setFrame(sprite->getFrame());
}
//
//
//
void Player::face_ball() {
  Engine::Compass to_ball;
  to_ball.direction = directionTo(match->ball);
  facing = to_ball.direction;
}
//
//
//
void Player::change_state(const player_state in_state) {
  switch (in_state) {
    case player_state::Stand:
      current_state = &state_stand;
      break;
    case player_state::Run:
      current_state = &state_run;
      break;
  }
}
