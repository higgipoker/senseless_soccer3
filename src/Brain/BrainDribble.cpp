#include "BrainDribble.hpp"

#include "Ball/Ball.hpp"
#include "Brain.hpp"
#include "Player/Player.hpp"
#include "Match/Match.hpp"
#include "Engine/Collider.hpp"
#include "Game/Game.hpp"
#define _USE_MATH_DEFINES

namespace Senseless {

// TODO
static const int turn_speed_ticks = 6;

BrainDribble::BrainDribble(Brain &in_brain) : BrainState(in_brain) {
    name       = "Dribble";
    next_state = brain_state::Wait;
}
void BrainDribble::start() {
    brain.player.current_speed = dribble_speeds[brain.player.speed];
    dribble_ticks              = 0;

    // start off dribbling in the direction we are facing ...
    // brain.locomotion.head(brain.player.getDirection().toVector());

    // ... and try dribble towards the opposition goal
    sf::Vector3f opposition_goal{brain.player.movable.position.x, Compass::toSfVector(brain.player.my_team->defending_goal).y, 0.F};
    turn_target_direction = Direction::South;
    if(Vector::outerProduct(brain.player.movable.position, brain.player.movable.velocity, opposition_goal) >=0) {
        rotate_direction = 45;
    } else {
        rotate_direction = -45;
    }
    if(turn_target_direction == Direction::South) rotate_direction = -rotate_direction;
    turning = true;
    // test
    next_state = brain_state::Retrieve;
}

void BrainDribble::step() {

    if(is_turning()) {
        if(++ticks_since_turn == turn_speed_ticks) {
            ticks_since_turn = 0;
            auto new_dir     = brain.player.movable.velocity;
            Vector::roundToAngle(new_dir, 45);
            Vector::normaliseToUnits(new_dir);
            Vector::rotate(new_dir, rotate_direction);
            brain.locomotion.head(new_dir);
        }
    } else {
        keep_in_pitch();
    }

}

void BrainDribble::stop() {
    brain.locomotion.stand();
}

bool BrainDribble::stateOver() {
    if(brain.player.ballInControlRange()) {
        return false;
    }
    return true;
}

void BrainDribble::turn(Direction target_dir) {
    turning = true;
    turn_target_direction  = target_dir;

    if(Vector::outerProduct(brain.player.movable.position, brain.player.movable.velocity, Compass(turn_target_direction).toSfVector()) >=0) {
        rotate_direction = 45;
    } else {
        rotate_direction = -45;
    }
    if(turn_target_direction == Direction::South) rotate_direction = -rotate_direction;
}

bool BrainDribble::is_turning() {
    if(turning && brain.player.getDirection() != turn_target_direction) {
        return true;
    }
    turning = false;
    return turning;
}

void BrainDribble::keep_in_pitch() {
    auto &pitch = *brain.player.match->pitch;
    // just keep inside the pitch for now
    sf::Vector3f topleft{pitch.getPointOfInterest(PitchPointsOfInterest::SideWest).x, pitch.getPointOfInterest(PitchPointsOfInterest::Bye, PitchPointOfInterestSide::North).y, 0};
    sf::Vector3f size{pitch.getPointOfInterest(PitchPointsOfInterest::SideEast).x - pitch.getPointOfInterest(PitchPointsOfInterest::SideWest).x,
                 pitch.getPointOfInterest(PitchPointsOfInterest::Bye, PitchPointOfInterestSide::South).y - pitch.getPointOfInterest(PitchPointsOfInterest::Bye, PitchPointOfInterestSide::North).y, 0};
    const auto player_position = brain.player.movable.position;
    const auto player_velocity = brain.player.movable.velocity;

    const sf::Vector3f north{player_position.x, topleft.y, 0.F};
    const sf::Vector3f south{player_position.x, topleft.y + size.y, 0.F};
    const sf::Vector3f west{topleft.x, player_position.y, 0.F};
    const sf::Vector3f east{topleft.x + size.x, player_position.y, 0.F};
    const float thresshold = 10;        
    
    // getting too close to north
    if(Vector::magnitude2d(player_position - north) < thresshold) {
        if(Vector::isMovingTowards(player_position, player_velocity, north)) {
            turn(Direction::South);
        }
    }

    // getting too close to south
    if(Vector::magnitude2d(south - player_position) < thresshold) {
        if(Vector::isMovingTowards(player_position, player_velocity, south)) {
            turn(Direction::North);
        }
    }

    // getting too close to east
    if(Vector::magnitude2d(east - player_position) < thresshold) {
        if(Vector::isMovingTowards(player_position, player_velocity, east)) {
            turn(Direction::West);
        }
    }

    // getting too close to west
    if(Vector::magnitude2d(player_position - west) < thresshold) {
        if(Vector::isMovingTowards(player_position, player_velocity, west)) {
            turn(Direction::East);
        }
    }
}
}  // namespace Senseless

