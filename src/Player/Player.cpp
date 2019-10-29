#include "Player.hpp"

#include "Engine/Collider.hpp"
#include "Engine/Compass.hpp"
#include "Engine/Debug.hpp"
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
  // make sure there is always a valid match when creating players
  assert(match && "match was not initied before constructing a player");

  std::cout << "player constructor" << std::endl;

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
void Player::update(const float in_dt) {
  Entity::update(in_dt);

  if (power_bar) {
    if (input) {
      if (!input->fireDown()) {
        power_bar->reset();
        power_bar->stop();
      }
    }
    power_bar->setPosition(
        movable.position.x - power_bar->getWidth() / 2,
        movable.position.y - player_sprite.getGlobalBounds().height);
    power_bar->update();
  }

  // state machine
  state->step();
  if (state->stateOver()) {
    state->stop();
    change_state(state->nextState());
    state->start();
    std::cout << "Player::update> " << state->name << std::endl;
  }

  feet.setCenter(movable.position.x, movable.position.y - feet.getRadius());
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

  if (DRAW_RAYS) {
    xray.setSize({10000, 1});
    xray.setPosition(0, feet.getCenter().y);
    xray.setFillColor(sf::Color::Magenta);
    sprite->debug_shapes.push_back(&xray);

    yray.setSize({1, 10000});
    yray.setPosition(feet.getCenter().x, 0);
    yray.setFillColor(sf::Color::Magenta);
    sprite->debug_shapes.push_back(&yray);
  }
}
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
void Player::onInputEvent(const InputEvent in_event,
                          const std::vector<int> &in_params) {
  std::cout << InputListener::toString(in_event) << std::endl;
  switch (in_event) {
    case InputEvent::FireDown:
      if (power_bar) {
        power_bar->reset();
        power_bar->start();
      }
      break;

    case InputEvent::FireUp: {
      if (ballInControlRange()) {
        std::cout << in_params.at(0) << std::endl;
        float p = in_params.at(0) * 0.3F;
        power_bar->reset();
        Vector3 f{facing.toVector()};
        f *= (p);
        f.z = p * 0.2F;
        match->getBall().kick(f);

        Vector3 spin = facing.toVector();
        spin.rotate(90);
        spin.normalise();
        spin *= 0.2F;
        //match->getBall().applySideSpin(spin);
        match->getBall().applyTopSpin(0.1F);
      }
    } break;

    case InputEvent::DoubleTap:
      power_bar->reset();
      break;

    case InputEvent::SingleTap:
      if (ball_under_control) {
        power_bar->reset();
        float p = 3;
        power_bar->reset();
        Vector3 f{facing.toVector()};
        f.normalise2d();
        f *= (p);
        match->getBall().kick(f);
      }
      break;
  }
}
