#include "Player.hpp"

#include "Engine/Collider.hpp"
#include "Engine/Compass.hpp"
#include "Engine/Debug.hpp"
#include "Match/Match.hpp"

using namespace Engine;
Match* Player::match = nullptr;

const int SHADOW_OFFSET_X = 1;
const int SHADOW_OFFSET_Y = 4;
//
//
//
Player::Player(PlayerSprite& in_sprite, PlayerShadowSprite& in_shadow)
    : Entity(movable, in_sprite, in_shadow),
      brain(*this),
      state_stand(*this),
      state_run(*this),
      state_dribble(*this),
      current_state(&state_stand),
      player_sprite(in_sprite),
      player_shadow(in_shadow) {
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
  Entity::Update();

  // either ai brain or controller (human brain)
  brain.update();
  // normalizes for diagonals
  if (Floats::greater_than(movable.velocity.magnitude(), 0)) {
    movable.velocity = movable.velocity.normalise2d();
  }

  feet.setPosition(movable.position.x - feet.getRadius(),
                   movable.position.y - feet.getRadius());
  control.setPosition(movable.position.x - control.getRadius(),
                      movable.position.y - control.getRadius());

  // state machine
  current_state->step();
  if (current_state->stateOver()) {
    current_state->stop();
    current_state->changeToNextState();
    current_state->start();
    std::cout <<"Player::update> " << current_state->name << std::endl;
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
      current_state = &state_stand;
      break;
    case player_state::Run:
      current_state = &state_run;
      break;
    case player_state::Dribble:
      current_state = &state_dribble;
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
bool Player::ballInControlRange(){
  return Collider::contains(control, match->ball->collidable);
}
//
//
//
void Player::close_control(){
  Vector3 f(feet.getPosition().x, feet.getPosition().y);
  Vector3 ball_pos = f + (facing.toVector() * 8);
  match->ball->movable.velocity.reset();
  match->ball->movable.velocity.reset();
  match->ball->movable.position = ball_pos;
}
//
//
//
Compass Player::direction(){
  return facing;
}
