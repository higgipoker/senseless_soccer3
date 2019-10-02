#include "Player.hpp"

#include "Engine/Collider.hpp"
#include "Engine/Compass.hpp"
#include "Engine/Debug.hpp"
#include "Match/Match.hpp"

using namespace Engine;
Match *Player::match = nullptr;

const int SHADOW_OFFSET_X = 1;
const int SHADOW_OFFSET_Y = 4;
//
//
//
Player::Player(PlayerSprite &in_sprite, PlayerShadowSprite &in_shadow)
  : Entity(in_sprite, in_shadow)
  , brain(*this)
  , state_stand(*this)
  , state_run(*this)
  , state_dribble(*this)
  , state(&state_stand)
  , player_sprite(in_sprite)
  , player_shadow(in_shadow) {
  feet.setRadius(3.0F);
  control.setRadius(15);
  feet.setFillColor(Debug::disgnostics_color);
  control.setFillColor(sf::Color::Transparent);
  control.setOutlineThickness(1);
  control.setOutlineColor(Debug::disgnostics_color);
}
//
//
//
void Player::update() {
  Entity::update();

  // either ai brain or controller (human brain)
  brain.update();

  // state machine
  state->step();
  if (state->stateOver()) {
    state->stop();
    change_state(state->nextState());
    state->start();
    std::cout << "Player::update> " << state->name << std::endl;
  }

  shadow.setFrame(sprite.getFrame());

#ifndef NDEBUG
  debug();
#endif
}
//
//
//
void Player::face_ball() {
  Compass to_ball;
  to_ball.direction = directionTo(*match->ball);
  facing.direction = to_ball.direction;
}
//
//
//
void Player::change_state(const player_state in_state) {
  switch (in_state) {
    case player_state::Stand:
      state = &state_stand;
      break;
    case player_state::Run:
      state = &state_run;
      break;
    case player_state::Dribble:
      state = &state_dribble;
      break;
  }
}
//
//
//
void Player::debug() {
  sprite.debug_shapes.clear();
  sprite.debug_shapes.push_back(&feet);
  sprite.debug_shapes.push_back(&control);
}
//
//
//
bool Player::ballInControlRange() {
  return Collider::contains(control, match->ball->collidable);
}
//
//
//
void Player::close_control() {
  Vector3 f(feet.getPosition().x, feet.getPosition().y);
  Vector3 ball_pos = f + (facing.toVector() * 8);
  match->ball->movable.velocity.reset();
  match->ball->movable.velocity.reset();
  match->ball->movable.position = ball_pos;
}
//
//
//
Compass Player::direction() {
  return facing;
}
