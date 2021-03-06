#include "Head.hpp"

#include "Player/Player.hpp"
namespace Senseless {
//
//
//
Head::Head(Player& in_player) : Locomotion(in_player) {}
//
//
//
void Head::init(sf::Vector3f in_direction) { direction = in_direction; }
//
//
//
void Head::start() { player.run(Compass(direction)); }
//
//
//
void Head::step() { stay_in_pitch(); }
//
//
//
void Head::stop() { player.movable.resetVelocity(); }
//
//
//
bool Head::finished() { return false; }
}  // namespace Senseless
