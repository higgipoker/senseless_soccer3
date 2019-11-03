#include "Head.hpp"

#include "Player/Player.hpp"
using namespace Engine;
//
//
//
Head::Head(Player& in_player) : Locomotion(in_player) {}
//
//
//
void Head::init(Vector3 in_direction) { direction = in_direction; }
//
//
//
void Head::start() { player.run(Compass(direction)); }
//
//
//
void Head::step() {stay_in_pitch();}
//
//
//
void Head::stop() { player.movable.resetVelocity(); }
//
//
//
bool Head::finished() { return false; }
