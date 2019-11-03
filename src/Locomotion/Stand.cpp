#include "Stand.hpp"

#include "Player/Player.hpp"
using namespace Engine;
//
//
//
Stand::Stand(Player& in_player) : Locomotion(in_player) {}
//
//
//
void Stand::init() {}
//
//
//
void Stand::start() { player.stopRunning(); }
//
//
//
void Stand::step() {}
//
//
//
void Stand::stop() {}
//
//
//
bool Stand::finished() { return false; }
