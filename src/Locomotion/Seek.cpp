#include "Seek.hpp"

#include "Player/Player.hpp"
namespace Senseless {
//
//
//
Seek::Seek(Player& in_player) : Locomotion(in_player) {}
//
//
//
void Seek::init(sf::Vector3f in_target) { target = in_target; }
//
//
//
void Seek::start() {
  player.run((target - player.movable.position));
  distance = Vector::magnitude(target - player.movable.position);
}
//
//
//
void Seek::step() {
  float new_distance =  Vector::magnitude(target - player.movable.position);

  if (new_distance > distance) {
    player.run((target - player.movable.position));
  }

  distance = new_distance;
  stay_in_pitch();
}
//
//
//
void Seek::stop() { player.stopRunning(); }
//
//
//
bool Seek::finished() { return Math::less_than(Vector::magnitude(target - player.movable.position), 5); }
}  // namespace Senseless
