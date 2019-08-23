#include "player.hpp"
#include "player_animations.h"

#include <cassert>

using namespace gamelib3;
namespace senseless_soccer3 {

std::map<Direction, std::string> Player::standmap;
std::map<Direction, std::string> Player::runmap;
std::map<Direction, std::string> Player::slidemap;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Player::Player() { width = 32; }
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Player::~Player() {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Player::PopulateAnimations() {
  assert(renderable);
  populate_animations(*this);
}
}  // namespace senseless_soccer3
