#include "Seek.hpp"

#include "Player/Player.hpp"
using namespace Engine;
//
//
//
Seek::Seek(Player & in_player) : Locomotion(in_player) {}
//
//
//
void Seek::init(Vector3 in_target) { target = in_target; }
//
//
//
void Seek::start() {
  player.run(Compass(target - player.movable.position));
}
//
//
//
void Seek::step() {stay_in_pitch();}
//
//
//
void Seek::stop() { player.stopRunning(); }
//
//
//
bool Seek::finished() {
  return Math::less_than((target - player.movable.position).magnitude(), 10);
}
