#include "Pursue.hpp"
#include "Engine/Compass.hpp"
#include "Player/Player.hpp"

using namespace Engine;
//
//
//
Pursue::Pursue(Player & in_player) : Locomotion(in_player) {}
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
  float distance = (target->position - player.movable.position).magnitude();
  if (Math::greater_than(distance, last_distance)) {
    Vector3 pos2d = target->position;
    pos2d.to2d();
    Vector3 heading = pos2d - player.movable.position;
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
