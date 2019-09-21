#include "Seek.hpp"
//
//
//
Seek::Seek(Engine::Movable& in_entity, Engine::Movable& in_target)
    : Locomotion(in_entity, in_target) {}
//
//
//
void Seek::start() {
  // nothing can fly in this game!
  entity.position.z = 0;

  // this will be normalised within player logic
  entity.velocity = target.position - entity.position;
}
//
//
//
void Seek::step() {}
//
//
//
void Seek::stop() {entity.velocity.reset();}
//
//
//
bool Seek::fiished() {
  return Engine::Floats::equal((target.position - entity.position).magnitude(),
                               0);
}
