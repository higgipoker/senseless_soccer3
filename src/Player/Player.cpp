#include "Player.hpp"

#include "Engine/Collider.hpp"
#include "Engine/Compass.hpp"
#include "Engine/Debug.hpp"
#include "Game/Game.hpp"
#include "Match/Match.hpp"

#include <cassert>
#include <iostream>

using namespace Engine;
Match *Player::match = nullptr;
//
//
//
Player::Player(UniquePtr<PlayerSprite> in_sprite,
               UniquePtr<PlayerSprite> in_shadow)
    : Entity(std::move(in_sprite), std::move(in_shadow)),
      brain(*this),
      state_stand(*this),
      state_run(*this),
      state_dribble(*this),
      state(&state_stand),
      player_sprite(static_cast<PlayerSprite &>(*sprite.get())),
      player_shadow(static_cast<PlayerSprite &>(*shadow.get())) {
  ball = &match->getBall();
  assert(ball);
  feet.setRadius(1.0F);
  control.setRadius(12);

  speed = RunningSpeed::Fast;
  current_speed = run_speeds[speed];

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
void Player::handleInput() {
  // input or brain
  if (input) {
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
  } else {
    brain.update();
  }
}
//
//
//
void Player::update() {
  Entity::update();

  // state machine
  state->step();
  if (state->stateOver()) {
    state->stop();
    change_state(state->nextState());
    state->start();
  }

  feet.setCenter(movable.position.x, movable.position.y - feet.getRadius());
  control.setCenter(feet.getCenter());
  shadow->setFrame(sprite->getFrame());
  distance_from_ball = distanceTo(match->getBall());

  if (power_bar) {
    power_bar->setCenter(
        sprite->getPosition().x,
        sprite->getPosition().y - sprite->getLocalBounds().height);
    power_bar->update();
  }

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
  direction.normalizeToUnits();
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
void Player::run(Engine::Compass in_direction) {
  Vector3 v = in_direction.toVector();
  v.normalise2d();
  v *= current_speed;
  movable.velocity = v;
}
//
//
//
void Player::run(Engine::Vector3 in_direction) {
  in_direction.normalise2d();
  in_direction *= current_speed;
  movable.velocity = in_direction;
}
//
//
//
void Player::stopRunning() { movable.resetVelocity(); }
//
//
//
void Player::kick(const float in_force) {
  Vector3 force = facing.toVector();
  force *= in_force;
  force.z = force.magnitude2d() * 0.2;
  ball->kick(force);
}
//
//
//
void Player::shortPass(Player &in_receiver) {
  float p = 7;
  Vector3 f{directionTo(*my_team->key_players.closest_to_ball)};
  f.normalise2d();
  f *= p;
  ball->kick(f);

  my_team->key_players.closest_to_ball->brain.changeState(brain_state::Retrieve);
}
//
//
//
void Player::onInputEvent(const InputEvent in_event,
                          const std::vector<int> &in_params) {
  std::cout << InputListener::toString(in_event) << std::endl;
  switch (in_event) {
    case InputEvent::FireDown:
      if (power_bar) {
        power_bar->start();
      }
      break;

    case InputEvent::FireUp: {
      if (ballInControlRange()) {
        assert(in_params.size());
        kick(fire_length_to_force(in_params[0]));
      }
      if (power_bar) {
        power_bar->stop();
        power_bar->reset();
      }
    } break;

    case InputEvent::DoubleTap:
      if (power_bar) {
        power_bar->stop();
        power_bar->reset();
      }
      break;

    case InputEvent::SingleTap:
      if (ball_under_control) {
        shortPass(*this);
      }
      if (power_bar) {
        power_bar->stop();
        power_bar->reset();
      }
      break;
  }
}
//
//
//
void Player::debug() {
  // change color if ball under control
  if (ballInControlRange()) {
    control.setOutlineColor(sf::Color::Green);
  } else {
    control.setOutlineColor(sf::Color::Red);
  }

  // change color if ball touching feet
  if (Collider::collides(feet, getMatch().getBall().collidable)) {
    feet.setFillColor(sf::Color::Red);
  }

  sprite->debug_shapes.clear();
  sprite->debug_shapes.push_back(&feet);
  sprite->debug_shapes.push_back(&control);

  if (DRAW_RAYS) {
    xray.setSize({world.width, 1});
    xray.setPosition(0, feet.getCenter().y);
    xray.setFillColor(sf::Color::Magenta);
    sprite->debug_shapes.push_back(&xray);

    yray.setSize({1, world.height});
    yray.setPosition(feet.getCenter().x, 0);
    yray.setFillColor(sf::Color::Magenta);
    sprite->debug_shapes.push_back(&yray);
  }
}
