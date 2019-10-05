#include "Seek.hpp"

using namespace Engine;
//
//
//
Seek::Seek(Movable& in_movable) : Locomotion(in_movable) {}
//
//
//
void Seek::init(Vector3 in_target) { target = in_target; }
//
//
//
void Seek::start() {
  entity.setVelocity(target - entity.getPosition());
}
//
//
//
void Seek::step() {}
//
//
//
void Seek::stop() { entity.setVelocity(Vector3{}); }
//
//
//
bool Seek::finished() {
  return Math::equal((target - entity.getPosition()).magnitude(), 0);
}
