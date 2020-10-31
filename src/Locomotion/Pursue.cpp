#include "Pursue.hpp"

#include "Engine/Compass.hpp"
#include "Player/Player.hpp"

namespace Senseless {
//
//
//
Pursue::Pursue(Player &in_player) : Locomotion(in_player) {}
//
//
//
void Pursue::init(Movable &in_target) { target = &in_target; }
//
//
//
void Pursue::start() {}
//
//
//
void Pursue::step() {
  // change direction when we stop getting closer to the target
  float distance = Vector::magnitude(target->position - player.movable.position);
  if (Math::greater_than(distance, last_distance)) {
    sf::Vector3f pos2d = target->position;
    Vector::to2d(pos2d);
    sf::Vector3f heading = pos2d - player.movable.position;
    player.run(heading);

    // todo: witha pathfinding algorithm, cpu controlled players should
    // work out a path based on 45 degree turns
    // entity.velocity.roundAngle(45);
    // entity.velocity.normalizeToUnits();
  }
  last_distance = distance;
  stay_in_pitch();
}
//
//
//
void Pursue::stop() { player.stopRunning(); }
//
//
//
bool Pursue::finished() { return false; }
}  // namespace Senseless
