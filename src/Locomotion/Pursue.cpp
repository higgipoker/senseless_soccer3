#include "Pursue.hpp"
//
//
//
Pursue::Pursue(Engine::Movable& in_movable) : Locomotion(in_movable) {}
//
//
//
void Pursue::init(Engine::Movable& in_target) { target = &in_target; }
//
//
//
void Pursue::start() {}
//
//
//
void Pursue::step() {
  entity.velocity = target->position.to2d() - entity.position;
  entity.velocity.roundAngle(45);
  entity.velocity.normalizeToUnits();
}
//
//
//
void Pursue::stop() { entity.velocity.reset(); }
//
//
//
bool Pursue::finished() { return false; }
//
//
//
PursueTilCaught::PursueTilCaught(Engine::Movable& in_movable, float in_range)
    : Pursue(in_movable), range(in_range) {}
//
//
//
void PursueTilCaught::init(Engine::Movable& in_target, float in_range) {
  target = &in_target;
  range = in_range;
}
//
//
//
bool PursueTilCaught::finished() {
  Engine::Vector3 distance = target->position.to2d() - entity.position;
  return (Engine::Floats::less_than(distance.magnitude(), range));
}
