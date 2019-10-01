#include "Pursue.hpp"
#include "Engine/Compass.hpp"
//
//
//
Pursue::Pursue(Engine::Movable &in_movable)
  : Locomotion(in_movable) {
}
//
//
//
void Pursue::init(Engine::Movable &in_target) {
  target = &in_target;
}
//
//
//
void Pursue::start() {
}
//
//
//
void Pursue::step() {
  // change direction when we stop getting closer to the target
  float distance = (target->position - entity.position).magnitude();
  if (Engine::Math::greater_than(distance, last_distance)) {
    Engine::Vector3 pos2d = target->position;
    pos2d.to2d();
    entity.velocity = pos2d - entity.position;

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
void Pursue::stop() {
  entity.velocity.reset();
}
//
//
//
bool Pursue::finished() {
  return false;
}
//
//
//
//
//
//
PursueTilCaught::PursueTilCaught(Engine::Movable &in_movable, float in_range)
  : Pursue(in_movable)
  , range(in_range) {
}
//
//
//
void PursueTilCaught::init(Engine::Movable &in_target, float in_range) {
  target = &in_target;
  range = in_range;
}
//
//
//
bool PursueTilCaught::finished() {
  Engine::Vector3 pos2d = target->position;
  pos2d.to2d();
  Engine::Vector3 distance = pos2d - entity.position;
  return (Engine::Math::less_than(distance.magnitude(), range));
}
