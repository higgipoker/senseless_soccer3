#include "Player.hpp"

Player::Player() {
  if (sprite) {
    player_sprite = static_cast<PlayerSprite*>(sprite);
  }
  if (shadow) {
    player_shadow = static_cast<PlayerSprite*>(shadow);
  }
}
