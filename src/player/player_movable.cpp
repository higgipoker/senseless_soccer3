#include "player_movable.hpp"
#include "player_animations.h"

#include <cassert>

using namespace gamelib3;
namespace senseless_soccer3 {

std::map<Direction, std::string> PlayerMovable::standmap;
std::map<Direction, std::string> PlayerMovable::runmap;
std::map<Direction, std::string> PlayerMovable::slidemap;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
PlayerMovable::PlayerMovable() {
  width = 32;
  co_friction = 0.1f;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
PlayerMovable::~PlayerMovable() {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void PlayerMovable::PopulateAnimations() {
  assert(renderable);
  populate_animations(*this);
}

}  // namespace senseless_soccer3
