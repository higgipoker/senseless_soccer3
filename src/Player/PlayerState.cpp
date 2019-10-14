#include "PlayerState.hpp"
//
#include "Player.hpp"

using namespace Engine;
//
//
//
PlayerState::PlayerState(Player &in_player) : player(in_player) {}
//
//
//
PlayerState::~PlayerState() {}
//
//
//
void PlayerState::step() { 
}
//
//
//
player_state PlayerState::nextState() { return next_state; }
