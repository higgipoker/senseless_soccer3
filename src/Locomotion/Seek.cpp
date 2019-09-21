#include "Seek.hpp"
//
//
//
Seek::Seek(Engine::Movable& in_movable) : Locomotion(in_movable) {}
//
//
//
void Seek::init(Engine::Vector3 in_target) { target = in_target; }
//
//
//
void Seek::start() {
  entity.velocity = target - entity.position;
  entity.velocity.normalizeToUnits();
}
//
//
//
void Seek::step() {}
//
//
//
void Seek::stop() { entity.velocity.reset(); }
//
//
//
bool Seek::finished() {
  return Engine::Floats::equal((target - entity.position).magnitude(), 0);
}
