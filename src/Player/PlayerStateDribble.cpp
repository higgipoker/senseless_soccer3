#include "PlayerStateDribble.hpp"

#include <iostream>

#include "Engine/Collider.hpp"
#include "Engine/Compass.hpp"
#include "Match/Match.hpp"
#include "Player.hpp"
#include "Game/Game.hpp"

// tmp lookup for kick force needed depeinding on player speed

namespace Senseless {
//
//
//
PlayerStateDribble::PlayerStateDribble (Player &in_player) : PlayerState (in_player) {
    name = "Dribble";
}
//
//
//
void PlayerStateDribble::start() {
    player.match->match->player_in_possession = &player;
    player.ball_under_control                     = true;
    already_kicked                                = false;
    player.current_speed                          = dribble_speeds[player.speed];
}
//
//
//
void PlayerStateDribble::close_control() {
    already_kicked = false;
    // edge of feet circle in direction of movement
    sf::Vector3f ball_position{player.feet.getCenter().x, player.feet.getCenter().y, 0};
    sf::Vector3f offset = player.facing.toSfVector() * (player.feet.getRadius() + player.match->ball->collidable.getRadius());
    Vector::move2d (ball_position, offset);

    // put the ball there
    player.match->ball->movable.place (ball_position);
}
//
//
//
void PlayerStateDribble::step() {
    PlayerState::step();

    // check for changed direction (close control)
    Compass old_direction = player.facing;
    sf::Vector3f dir           = player.movable.velocity;
    player.facing.fromSfVector (dir);
    if (old_direction.direction != player.facing.direction) {
        close_control();
    } else {
        // check for collision with ball
        if (Collider::collides (player.feet, player.match->ball->collidable)) {
            if (!already_kicked) {
                kick();
            }
        } else {
            already_kicked = false;
        }
    }

    player.player_sprite.setPlayerAnimation (PlayerAnimationType::Run, player.facing.direction);

    player.calc_short_pass_candidates();
}
//
//
//
void PlayerStateDribble::stop() {
    if (player.match->match->player_in_possession == &player) {
        player.match->match->player_in_possession = nullptr;
    }
    player.ball_under_control = false;
}
//
//
//
bool PlayerStateDribble::stateOver() {
    // check if ball is outside control range
    if (!player.ballInControlRange()) {
        next_state = player_state::Run;
        return true;
    }
    // or if we stopped moving
    if (Math::equal (Vector::magnitude2d(player.movable.velocity), 0)) {
        next_state = player_state::Stand;
        return true;
    }

    return false;
}
//
//
//
void PlayerStateDribble::kick() {
    already_kicked = true;
    float force    = kick_mods[static_cast<RunningSpeed> (player.speed)];
    auto  f        = Vector::magnitude2d(player.movable.velocity);
    f++;
    sf::Vector3f kick_force = Compass (player.facing).toSfVector();
    Vector::normalise2d(kick_force);
    kick_force *= force;
    player.match->ball->kick (kick_force);
}
}  // namespace Senseless
