#include "BrainDribble.hpp"

#include "Ball/Ball.hpp"
#include "Brain.hpp"
#include "Player/Player.hpp"
#include "Match/Match.hpp"
#include "Engine/Collider.hpp"
namespace Senseless {
static const int DRIBBLE_TIME = 100;
//
//
//
BrainDribble::BrainDribble(Brain& in_brain) : BrainState(in_brain), pattern(&pattern_random) {
    name       = "Dribble";
    next_state = brain_state::Wait;
    if(brain.persist){
        next_state = brain_state::Retrieve;
    }
}
//
//
//
void BrainDribble::start() {
    brain.player.current_speed = dribble_speeds[brain.player.speed];
    dribble_ticks              = 0;
    brain.locomotion.head(brain.player.getDirection().toVector());
}
//
//
//
void BrainDribble::step() {
    // just keep inside the pitch for now
    const auto    bounds          = brain.player.match.getPitch().getDimensions().bounds;
    auto    player_position = brain.player.match.getPitch().toPitchSpace(brain.player.movable.position);
    auto    player_velocity = brain.player.movable.velocity;
    Vector3 north{player_position.x, bounds.getPosition().y};
    Vector3 south{player_position.x, bounds.getPosition().y + bounds.getSize().y};
    Vector3 west{bounds.getPosition().x, player_position.y};
    Vector3 east{bounds.getPosition().x + bounds.getSize().x, player_position.y};

    static const float thresshold = 20;


    // getting too close to north
    if ((north-player_position).magnitude2d() < thresshold) {
        if (player_position.isMovingTowards(north, player_velocity)) {
            turn();
        }
    }

    // getting too close to south
    else if ((south-player_position).magnitude2d() < thresshold) {
        if (player_position.isMovingTowards(south, player_velocity)) {
            turn();
        }
    }

    // getting too close to east
    else if ((east - player_position).magnitude2d() < thresshold) {
        if (player_position.isMovingTowards(east, player_velocity)) {
            turn();
        }
    }

    // getting too close to west
    else if ((west-player_position).magnitude2d() < thresshold) {
        if (player_position.isMovingTowards(west, player_velocity)) {
            turn();
        }
    }

    // somehow we got outside the pitch
    if(!Collider::contains(bounds, player_position)&&!waiting_for_reenter_bounds){
        turn();
        waiting_for_reenter_bounds = true;
    }else{
        waiting_for_reenter_bounds = false;
    }

    if(is_turning()){
        auto new_dir= brain.player.movable.velocity;
        new_dir.rotate(45);
        brain.locomotion.head(new_dir);
    }

    //    if (++dribble_ticks > DRIBBLE_TIME && !brain.player.short_pass_candidates.empty()) {
    //        brain.changeState(brain_state::Pass);

    //    } else {
    //        const auto bounds = brain.player.match.getPitch().getDimensions().bounds;
    //        const auto center = bounds.getCenter();

    //        Vector3 player_position = brain.player.match.getPitch().toPitchSpace(brain.player.movable.position);
    //        if (!Collider::contains(bounds, player_position)) {
    //            brain.locomotion.head(player_position - center);
    //        }
    //        if (pattern->changeDirection()) {
    //            keep_in_pitch();
    //            brain.locomotion.head(pattern->nextDirection(brain.player.movable.position, brain.player.movable.velocity).toVector());
    //        }
    //    }
}
//
//
//
void BrainDribble::stop() {
    brain.locomotion.stand();
}
//
//
//
bool BrainDribble::stateOver() {
    if (brain.player.ballInControlRange()) {
        return false;
    }
    return true;
}
//
//
//
void BrainDribble::turn() {
    turning               = true;
    Vector3 reversed      = brain.player.movable.velocity;
    reversed.reverse();
    turn_target_direction = Compass(reversed).direction;
}
//
//
//
bool BrainDribble::is_turning() {
    if (turning && brain.player.getDirection() != turn_target_direction) {
        return true;
    } else {
        turning = false;
    }
    return turning;
}
//
//
//
void BrainDribble::keep_in_pitch() {
    const auto bounds = brain.player.match.getPitch().getDimensions().bounds;
    const auto center = bounds.getCenter();

    Vector3 player_position = brain.player.match.getPitch().toPitchSpace(brain.player.movable.position);
    Vector3 player_velocity = brain.player.movable.velocity;

    Vector3 north{player_position.x, bounds.getPosition().y};
    Vector3 south{player_position.x, bounds.getPosition().y + bounds.getSize().y};
    Vector3 west{bounds.getPosition().y, player_position.y};
    Vector3 east{bounds.getPosition().y + bounds.getSize().y, player_position.y};

    static const float thresshold = 200;

    // north
    if ((Vector3::distance_to(player_position, north) < thresshold) && player_position.isMovingTowards(north, player_velocity)) {
        pattern->correctCourse(center);
    }

    // south
    if ((Vector3::distance_to(player_position, south) < thresshold) && player_position.isMovingTowards(south, player_velocity)) {
        pattern->correctCourse(center);
    }

    // west
    if ((Vector3::distance_to(player_position, west) < thresshold) && player_position.isMovingTowards(west, player_velocity)) {
        pattern->correctCourse(center);
    }

    // east
    if ((Vector3::distance_to(player_position, east) < thresshold) && player_position.isMovingTowards(east, player_velocity)) {
        pattern->correctCourse(center);
    }
}
}  // namespace Senseless
