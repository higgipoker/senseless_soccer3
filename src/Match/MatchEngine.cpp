#include "MatchEngine.hpp"
using namespace Engine;
namespace MatchEngine {
//
//
//
void think(Player &player, const Match & match) {
    switch (match.state) {
        case MatchState::PreGame:
            break;
        case MatchState::KickOff:
            break;
        case MatchState::Play:
            break;
        case MatchState::GoalKick:
            break;
        case MatchState::Corner:
            break;
        case MatchState::FreeKick:
            break;
        case MatchState::ThrowIn:
            break;
        case MatchState::HalfTime:
            break;
    }

    Vector3 target;
    player.force = player.position - target;
}
//
//
//
void simulate(Player &player, const float dt) {
    Vector3 acceleration = player.force / player.mass;
    player.velocity += acceleration * dt;
    player.position += player.velocity * dt;
}
//
//
//
void MatchEngine::start() {
}
//
//
//
void MatchEngine::update() {
    for (auto &player : players) {
        think(player, match);
        simulate(player, 0.01F);
    }
}
}  // namespace MatchEngine
