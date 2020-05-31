#include "BrainDribble.hpp"

#include "Ball/Ball.hpp"
#include "Brain.hpp"
#include "Player/Player.hpp"
#include "Match/Match.hpp"
#include "Engine/Collider.hpp"
#include "Game/Game.hpp"

namespace Senseless {
BrainDribble::BrainDribble(Brain& in_brain) : BrainState(in_brain), pattern(&pattern_random) {
    name       = "Dribble";
    next_state = brain_state::Wait;
}
void BrainDribble::start() {
    brain.player.current_speed = dribble_speeds[brain.player.speed];
    dribble_ticks              = 0;
    brain.locomotion.head(brain.player.getDirection().toVector());

    // test
    next_state = brain_state::Retrieve;
}

void BrainDribble::step() {
    const auto& pitch = *brain.player.gamestate->pitch;
    // just keep inside the pitch for now
    Vector3 topleft{pitch.getPointOfInterest(PitchPointsOfInterest::SideWest).x, pitch.getPointOfInterest(PitchPointsOfInterest::Bye, PitchPointOfInterestSide::North).y};
    Vector3 size{pitch.getPointOfInterest(PitchPointsOfInterest::SideEast).x - pitch.getPointOfInterest(PitchPointsOfInterest::SideWest).x,
                 pitch.getPointOfInterest(PitchPointsOfInterest::Bye, PitchPointOfInterestSide::North).y - pitch.getPointOfInterest(PitchPointsOfInterest::Bye, PitchPointOfInterestSide::South).y};

    // to world coordinates
    topleft = pitch.toScreenSpace(topleft);

    const auto player_position = brain.player.movable.position;
    const auto player_velocity = brain.player.movable.velocity;

    const Vector3 north{player_position.x, topleft.y};
    const Vector3 south{player_position.x, topleft.y + size.y};
    const Vector3 west{topleft.x, player_position.y};
    const Vector3 east{topleft.x + size.x, player_position.y};

    static const float thresshold = 10;

    std::cout << ((player_position - west).magnitude2d()) << std::endl;

    // getting too close to north
    if ((player_position - north).magnitude2d() < thresshold) {
        if (Vector3::isMovingTowards(player_position, player_velocity, north)) {
            turn();
        }
    }

    // getting too close to south
    if ((south - player_position).magnitude2d() < thresshold) {
        if (Vector3::isMovingTowards(player_position, player_velocity, south)) {
            turn();
        }
    }

    // getting too close to east
    if ((east - player_position).magnitude2d() < thresshold) {
        if (Vector3::isMovingTowards(player_position, player_velocity, east)) {
            turn();
        }
    }

    // getting too close to west
    if ((player_position - west).magnitude2d() < thresshold) {
        if (Vector3::isMovingTowards(player_position, player_velocity, west)) {
            std::cout << "moving west" << std::endl;
            turn();
        }
    }

    if (is_turning()) {
        auto new_dir = brain.player.movable.velocity;
        new_dir.rotate(-45);
        brain.locomotion.head(new_dir);
    }
}

void BrainDribble::stop() {
    brain.locomotion.stand();
}

bool BrainDribble::stateOver() {
    if (brain.player.ballInControlRange()) {
        return false;
    }
    return true;
}

void BrainDribble::turn() {
    turning         = true;
    Vector3 rotated = brain.player.movable.velocity;
    rotated.rotate(-45);
    turn_target_direction = Compass(rotated).direction;
}

bool BrainDribble::is_turning() {
    if (turning && brain.player.getDirection() != turn_target_direction) {
        return true;
    }
    turning = false;
    return turning;
}
}  // namespace Senseless
