#include "BrainSupport.hpp"

#include "Brain.hpp"

#include "Engine/Compass.hpp"
#include "Match/Match.hpp"
#include "Player/Player.hpp"
#include "Team/Team.hpp"

using namespace Engine;
//
//
//
BrainSupport::BrainSupport(Brain& in_brain) : BrainState(in_brain) {
    name = "Support";
    radius.setRadius(800);
}
//
//
//
void BrainSupport::start() {
    // tmp just run around randomly until we get too far from the player in
    // possession
    // change_direction();
    auto r = Compass::getRandomDirection();
    brain.locomotion.head(r.toVector());
}
//
//
//
void BrainSupport::step() {
    int CHANGE_TICKS = brain.player.support_type % 2 == 0 ? 150 : 50;

    auto pos = brain.player.match.getBall().movable.position.toSfVector();
    radius.setCenter(pos);

    auto dist = brain.player.distanceTo(brain.player.match.getBall());
    if (dist > radius.getRadius()) {
        ticks_since_change = 0;
        Compass new_direction = brain.player.directionTo(brain.player.match.getBall());
        brain.locomotion.head(new_direction.toVector());
    }

    else if (++ticks_since_change > CHANGE_TICKS) {
        ticks_since_change = 0;
        change_direction();
    }
}
//
//
//
void BrainSupport::stop() {
}
//
//
//
bool BrainSupport::stateOver() {
    if (brain.player.ballInControlRange()) {
        next_state = brain_state::Dribble;
        return true;
    }
    return false;
}
//
//
//
void BrainSupport::change_direction() {
    Compass new_direction = Compass::getRandomDirection();
    while (new_direction == brain.player.getDirection()) {
        new_direction = Compass::getRandomDirection();
    }
    brain.locomotion.head(new_direction.toVector());
}
