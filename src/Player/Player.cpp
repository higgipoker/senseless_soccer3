#include "Player.hpp"
//
#include "Game/Game.hpp"
#include "Match/Match.hpp"
#include "Team/Team.hpp"
//
#include "Engine/Collider.hpp"
#include "Engine/Compass.hpp"
#include "Engine/Debug.hpp"
//
#include <iostream>
namespace Senseless {
//
//
//
std::map<brain_state, std::string> Player::brainstates = {
    {brain_state::Idle, "Idle"},
    {brain_state::Cover, "Cover"},
    {brain_state::Support, "Support"},
    {brain_state::Retrieve, "Retrieve"},
    {brain_state::Dribble, "Dribble"},
    {brain_state::Pass, "Pass"},
    {brain_state::Wait, "Wait"},
};
//
//
//
int Player::instances = 0;
//
//
//
Player::Player(std::unique_ptr<PlayerSprite> in_sprite, std::unique_ptr<PlayerSprite> in_shadow)
    : Entity(std::move(in_sprite), std::move(in_shadow)),
      state_stand(*this),
      state_run(*this),
      state_dribble(*this),
      state(&state_stand),
      brain(*this),
      player_sprite(static_cast<PlayerSprite &>(*renderable.sprite)),
      player_shadow(static_cast<PlayerSprite &>(*renderable.shadow)) {
    type = EntityType::Player;
    feet.setRadius(4.0F);
    control.setRadius(14);
    speed         = RunningSpeed::Fast;
    current_speed = run_speeds[speed];

    // debug
    feet.setFillColor(Debug::defaultDiagnosticsColor());
    control.setFillColor(sf::Color::Transparent);
    control.setOutlineThickness(1);
    control.setOutlineColor(Debug::defaultDiagnosticsColor());
    ++instances;
    std::cout << instances << " players" << std::endl;
}
//
//
//
Player::~Player() {
    --instances;
    std::cout << instances << " players" << std::endl;
}
//
//
//
void Player::setTeamData(TeamData in_data) {
    team_data = in_data;
}
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
    }
}
//
//
//
void Player::update(const float in_dt) {
    if (!input) {
        brain.think();
    }
    Entity::update(in_dt);

    short_pass_triangle.reset();
    short_pass_triangle.setFillColor({255, 0, 0, 70});

    // state machine
    state->step();
    if (state->stateOver()) {
        state->stop();
        change_state(state->nextState());
        state->start();
    }

    feet.setCenter(movable.position.x, movable.position.y - feet.getRadius());
    control.setCenter(feet.getCenter());
    distance_from_ball   = Vector3::distance_to(movable.position, gamestate->ball->movable.position);
    renderable.sprite->z = movable.position.y;

#ifndef NDEBUG
    debug();
#endif
}
//
//
//
void Player::face_ball() {
    auto direction = Vector3::direction_to(movable.position, gamestate->ball->movable.position);
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
    return Collider::contains(control, gamestate->ball->collidable);
}
//
//
//
Compass Player::getDirection() {
    return facing;
}
//
//
//
Brain &Player::getBrain() {
    return brain;
}
//
//
//
void Player::run(Compass in_direction) {
    Vector3 v = in_direction.toVector();
    v.normalise2d();
    v *= current_speed;
    movable.velocity = v;
}
//
//
//
void Player::run(Vector3 in_direction) {
    in_direction.normalise2d();
    in_direction *= current_speed;
    movable.velocity = in_direction;
}
//
//
//
void Player::stopRunning() {
    movable.resetVelocity();
}
//
//
//
void Player::kick(const float in_force) {
    Vector3 force = facing.toVector();
    force *= in_force;
    force.z = force.magnitude2d() * 0.2F;
    gamestate->ball->kick(force);
}
//
//
//
void Player::shortPass(Player &in_receiver) {
    float distance     = Vector3::distance_to(movable.position, in_receiver.movable.position);
    float force_needed = 2;

    auto it = pass_distance.begin();
    while (*it < distance && force_needed <= 13) {
        ++it;
        ++force_needed;
    }

    Vector3 force = Vector3::direction_to(movable.position, in_receiver.movable.position);
    force.setMagnitude(force_needed);
    gamestate->ball->kick(force);
    in_receiver.brain.changeState(brain_state::Retrieve);
}
//
//
//
void Player::onInputEvent(const InputEvent in_event, const std::vector<int> &in_params) {
    switch (in_event) {
        case InputEvent::FireDown:
            break;

        case InputEvent::FireUp: {
            if (ballInControlRange()) {
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
            short_pass_candidates.push_back(player);
            short_pass_triangle.setFillColor({0, 255, 0, 70});
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
    if (Collider::collides(feet, gamestate->ball->collidable)) {
        feet.setFillColor(sf::Color::Green);
    }

    renderable.sprite->debug_shapes.clear();
    renderable.sprite->debug_shapes.push_back(&feet);
    renderable.sprite->debug_shapes.push_back(&control);

    if (DRAW_RAYS) {
        xray.setSize({world.width, 1});
        xray.setPosition(0, feet.getCenter().y);
        xray.setFillColor(sf::Color::Magenta);
        renderable.sprite->debug_shapes.push_back(&xray);

        yray.setSize({1, world.height});
        yray.setPosition(feet.getCenter().x, 0);
        yray.setFillColor(sf::Color::Magenta);
        renderable.sprite->debug_shapes.push_back(&yray);
    }
    renderable.sprite->debug_shapes.push_back(&short_pass_triangle);
}
//
//
//
void Player::setPlayingPosition(std::unique_ptr<PlayingPosition> in_position) {
    playing_position = std::move(in_position);
}
//
//
//
void Player::goToSetPiecePosition(const Situation in_situation, const Direction in_pitch_side) {
    if (auto position = playing_position.get()) {
        brain.changeState(brain_state::Idle);
        brain.locomotion.seek(position->getTargetPosition(in_situation, *gamestate->ball, in_pitch_side));
    }
}
}  // namespace Senseless
