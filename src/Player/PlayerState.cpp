#include "PlayerState.hpp"

#include "Player.hpp"
//
//
//
PlayerState::PlayerState(Player& in_player) : player(in_player) {}
//
//
//
PlayerState::~PlayerState() {}
//
//
//
void PlayerState::changeToNextState() { player.change_state(next_state); }
