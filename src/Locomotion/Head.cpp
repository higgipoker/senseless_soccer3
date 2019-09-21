#include "Head.hpp"
//
//
//
Head::Head(Engine::Movable& in_entity) : Locomotion(in_entity) {}
//
//
//
void Head::init(Engine::Vector3 in_direction) { direction = in_direction; }
//
//
//
void Head::start() {
  entity.velocity = direction;
  entity.velocity.normalizeToUnits();
}
//
//
//
void Head::step() {}
//
//
//
void Head::stop() { entity.velocity.reset(); }
//
//
//
bool Head::finished() { return false; }
