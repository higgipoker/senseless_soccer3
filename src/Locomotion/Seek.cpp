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
  player.run(Compass(target - player.movable.getPosition()));
}
//
//
//
void Seek::step() {}
//
//
//
void Seek::stop() { player.stopRunning(); }
//
//
//
bool Seek::finished() {
  return Math::equal((target - player.movable.getPosition()).magnitude(), 0);
}
