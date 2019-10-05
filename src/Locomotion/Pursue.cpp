#include "Pursue.hpp"
#include "Engine/Compass.hpp"

using namespace Engine;
//
//
//
Pursue::Pursue(Movable &in_movable) : Locomotion(in_movable) {}
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
  float distance = (target->getPosition() - entity.getPosition()).magnitude();
  if (Math::greater_than(distance, last_distance)) {
    Vector3 pos2d = target->getPosition();
    pos2d.to2d();
    Vector3 heading = pos2d - entity.getPosition();
    heading.normalise();
    entity.setVelocity(heading);

    // todo: witha pathfinding algorithm, cpu controlled players should
    // work out a path based on 45 degree turns
    // entity.velocity.roundAngle(45);
    // entity.velocity.normalizeToUnits();
  }
  last_distance = distance;
}
//
//
//
void Pursue::stop() { entity.setVelocity(Vector3{}); }
//
//
//
bool Pursue::finished() { return false; }
//
//
//
//
//
//
PursueTilCaught::PursueTilCaught(Movable &in_movable, float in_range)
    : Pursue(in_movable), range(in_range) {}
//
//
//
void PursueTilCaught::init(Movable &in_target, float in_range) {
  target = &in_target;
  range = in_range;
}
//
//
//
bool PursueTilCaught::finished() {
  Vector3 pos2d = target->getPosition();
  pos2d.to2d();
  Vector3 distance = pos2d - entity.getPosition();
  return (Math::less_than(distance.magnitude(), range));
}
