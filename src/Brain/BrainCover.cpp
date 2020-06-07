#include "BrainCover.hpp"

#include "Brain.hpp"
#include "Engine/Compass.hpp"
#include "Match/Match.hpp"
#include "Player/Player.hpp"
#include "Team/Team.hpp"
#include "Game/Game.hpp"

namespace Senseless {
//
//
//
BrainCover::BrainCover(Brain &in_brain) : BrainState(in_brain) {
    name = "Cover";
}
//
//
//
void BrainCover::start() {
    if(auto position = brain.player.playing_position.get()) {
            auto target = position->getTargetPosition(Situation::Playing, *brain.player.match->ball);
            brain.locomotion.seek(target);
            last_target = target;
        }
}
//
//
//
void BrainCover::step() {
    if(auto position = brain.player.playing_position.get()) {
            auto target = position->getTargetPosition(Situation::Playing, *brain.player.match->ball);
            auto dist = (brain.player.movable.position - target).magnitude2d();
            if(Math::greater_than(dist, 1) &&
                    Math::greater_than((target - last_target).magnitude2d(), 1)) {
                    brain.locomotion.seek(target);
                    last_target = target;
                }
        }
}
//
//
//
void BrainCover::stop() {}
//
//
//
bool BrainCover::stateOver() {
    if(should_close_down()) {
            next_state = brain_state::Retrieve;
            return true;
        }
    return false;
}
//
//
//
bool BrainCover::should_close_down() {
    // if the ball is loose and i am closest to the ball -> definitely close down
//  if (brain.player.match->player_in_possession == nullptr) {
//    if (brain.player.my_team.closest_to_ball == &brain.player) {
//      std::cout << brain.player.name << " closing down" << std::endl;
//      return true;
//    }
//  }

    return false;
}
}  // namespace Senseless
