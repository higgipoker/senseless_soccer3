#include "BrainCover.hpp"

#include "Brain.hpp"

#include "Engine/Compass.hpp"
#include "Match/Match.hpp"
#include "Player/Player.hpp"
#include "Team/Team.hpp"

using namespace Engine;
//
//
//
BrainCover::BrainCover(Brain& in_brain) : BrainState(in_brain) {
    name = "Cover";
}
//
//
//
void BrainCover::start() {
}
//
//
//
void BrainCover::step() {
    std::cout << "position: " << brain.player.movable.position.x << ", " << brain.player.movable.position.y
              << std::endl;
    if (auto position = brain.player.playing_position.get()) {
        auto target = position->getTargetPosition(brain.player.match.getPitch(), brain.player.team, brain.player.team,
                                                  brain.player.match.getBall());

        auto dist = (brain.player.movable.position - target).magnitude2d();
        if (Math::greater_than(dist, 1) && Math::greater_than((target - last_target).magnitude2d(), 1)) {
            brain.locomotion.seek(target);
            last_target = target;
            std::cout << "target: " << target.x << ", " << target.y << std::endl;
        }
    }
}
//
//
//
void BrainCover::stop() {
}
//
//
//
bool BrainCover::stateOver() {
    return false;
}