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

  short_pass_triangle.reset();
  short_pass_triangle.setFillColor({0, 255, 0, 70});

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
  ball->start_recording_distance();
}
//
//
//
inline float MIN_KICK_FORCE = 3;
inline float MAX_KICK_FORCE = 100;
void Player::shortPass(Player &in_receiver) {
  float distance = distanceTo(in_receiver);
  float force_needed = 2;

  auto it = pass_distance.begin();
  while (*it < distance && force_needed <= 13) {
    ++it;
    ++force_needed;
  }

  Vector3 force = directionTo(in_receiver);
  force.setMagnitude(force_needed);
  ball->kick(force);
  in_receiver.brain.changeState(brain_state::Retrieve);
  my_team->key_players.pass_receiver = &in_receiver;
  ball->start_recording_distance();
}
//
//
//
void Player::onInputEvent(const InputEvent in_event,
                          const std::vector<int> &in_params) {
  switch (in_event) {
    case InputEvent::FireDown:
      break;

    case InputEvent::FireUp: {
      if (ballInControlRange()) {
        assert(in_params.size());
        kick(in_params[0]);
      }
    } break;

    case InputEvent::DoubleTap:
      break;

    case InputEvent::SingleTap:
      if (ball_under_control) {
        if (!short_pass_candidates.empty()) {
          shortPass(*short_pass_candidates[0]);
        } else {
          kick(3);
        }
      }
      break;
  }
}
/* --------------------------------------------------
       [PLAYER]

          p1
          /\
         /  \
        /    \
       /      \
     p2--------p3

  calc_short_pass_recipients
-------------------------------------------------- */
void Player::calc_short_pass_candidates() {
  // current position plus projected away from feet slightly
  Vector3 t1 = movable.position + facing.toVector() * 10;

  // rotate x degrees and project out
  Vector3 temp1 = facing.toVector();
  temp1.rotate(40, 0, 0);
  temp1.normalise();
  temp1 *= 450;
  Vector3 t2 = movable.position + temp1;

  // rotate minus x degrees and project out
  Vector3 temp2 = facing.toVector();
  temp2.rotate(-40, 0, 0);
  temp2.normalise();
  temp2 *= 450;
  Vector3 t3 = movable.position + temp2;

  // save 3 points to triangle
  short_pass_triangle.setPoints({t1.x, t1.y}, {t2.x, t2.y}, {t3.x, t3.y});

  // tmp
  short_pass_candidates.clear();
  // get a list of players in my short pass range
  for (auto &player : my_team->players) {
    // is in short pass range
    if (Collider::collides(player->movable.position, short_pass_triangle)) {
      short_pass_candidates.push_back(player.get());
      short_pass_triangle.setFillColor({255, 0, 0, 70});
    }
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

  sprite->debug_shapes.push_back(&short_pass_triangle);
}
