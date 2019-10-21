#include "Player.hpp"

#include "Engine/Collider.hpp"
#include "Engine/Compass.hpp"
#include "Engine/Debug.hpp"
#include "Match/Match.hpp"

#include <cassert>
#include <iostream>

using namespace Engine;
Match *Player::match = nullptr;

const int SHADOW_OFFSET_X = 1;
const int SHADOW_OFFSET_Y = 4;
//
//
//
Player::Player(UnqPtr<PlayerSprite> in_sprite, UnqPtr<PlayerSprite> in_shadow)
    : Entity(std::move(in_sprite), std::move(in_shadow)),
      brain(*this),
      state_stand(*this),
      state_run(*this),
      state_dribble(*this),
      state(&state_stand),
      player_sprite(static_cast<PlayerSprite &>(*sprite.get())),
      player_shadow(static_cast<PlayerSprite &>(*shadow.get())) {
  // make sure there is always a valid match when creating players
  assert(match);

  feet.setRadius(1.0F);
  control.setRadius(12);

  speed = RunningSpeed::Fast;

  // debug
  feet.setFillColor(Debug::defaultDiagnosticsColor());
  control.setFillColor(sf::Color::Transparent);
  control.setOutlineThickness(1);
  control.setOutlineColor(Debug::defaultDiagnosticsColor());
}
//
//
//
void Player::setTeamData(TeamData in_data) { team_data = in_data; }
//
//
//
void Player::handleInput() {  // Entity::handleInput();
  if (!input) return;

  // no momentum system for player movement, just set velocity

  Vector3 movement_vector;
  if (input->up()) {
    movement_vector.y = -1;
  }
  if (input->down()) {
    movement_vector.y = 1;
  }
  if (input->left()) {
    movement_vector.x = -1;
  }
  if (input->right()) {
    movement_vector.x = 1;
  }
  run(movement_vector);
}
//
//
//
void Player::update() {
  Entity::update();

  if (power_bar) {
    power_bar->setPosition(movable.getPosition().x, movable.getPosition().y);
    power_bar->update();
  }

  // either ai brain or controller (human brain)
  if (!input) {
    brain.update();
  }

  // state machine
  state->step();
  if (state->stateOver()) {
    state->stop();
    change_state(state->nextState());
    state->start();
    std::cout << "Player::update> " << state->name << std::endl;
  }

  feet.setCenter(movable.getX(), movable.getY() - feet.getRadius());
  control.setCenter(feet.getCenter());
  shadow->setFrame(sprite->getFrame());

#ifndef NDEBUG
  debug();
#endif
}
//
//
//
void Player::face_ball() {
  auto direction = directionTo(getMatch().getBall());
  direction.roundAngle(45);
  Compass to_ball(direction);
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
bool Player::ballInControlRange() {
  return Collider::contains(control, getMatch().getBall().collidable);
}
//
//
//
Compass Player::getDirection() { return facing; }
//
//
//
Brain &Player::getBrain() { return brain; }
//
//
//
void Player::connectMatch(Match &in_match) { match = &in_match; }
//
//
//
Match &Player::getMatch() { return *match; }
//
//
//
void Player::debug() {
  // change color if ball under control
  if (ball_under_control) {
    control.setOutlineColor(sf::Color::Red);
  }

  // change color if ball touching feet
  if (Collider::collides(feet, getMatch().getBall().collidable)) {
    feet.setFillColor(sf::Color::Red);
  }

  sprite->debug_shapes.clear();
  sprite->debug_shapes.push_back(&feet);
  sprite->debug_shapes.push_back(&control);
}
//
//
//
void Player::run(Engine::Compass in_direction) {
  Vector3 v = in_direction.toVector();
  v.normalise2d();
  v *= movable.speed;
  movable.setVelocity(v);
}
//
//
//
void Player::run(Engine::Vector3 in_direction) {
  in_direction.normalise2d();
  in_direction *= movable.speed;
  movable.setVelocity(in_direction);
}
//
//
//
void Player::stopRunning() { movable.resetVelocity(); }
//
//
//
void Player::pass(Engine::Vector3 in_force) { match->getBall().kick(in_force); }
//
//
//
void Player::pass(Player &in_receiver) {
  Vector3 force = directionTo(in_receiver);
  int force_needed = 10;
  force *= force_needed;
  match->getBall().kick(force);
}
//
//
//
void Player::onEvent(const InputEvent in_event,
                     const std::vector<int> &in_params) {
  switch (in_event) {
    case InputEvent::FireDown:
      break;
    case InputEvent::FireUp:
    case InputEvent::DoubleTap:
    case InputEvent::SingleTap:
      std::cout << InputListener::toString(in_event) << std::endl;
      break;
  }
}
