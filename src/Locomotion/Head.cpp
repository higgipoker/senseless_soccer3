#include "Head.hpp"

using namespace Engine;
//
//
//
Head::Head(Movable& in_entity) : Locomotion(in_entity) {}
//
//
//
void Head::init(Vector3 in_direction) { direction = in_direction; }
//
//
//
void Head::start() {
  entity.setVelocity( direction);
}
//
//
//
void Head::step() {}
//
//
//
void Head::stop() { entity.setVelocity(Vector3{}); }
//
//
//
bool Head::finished() { return false; }
