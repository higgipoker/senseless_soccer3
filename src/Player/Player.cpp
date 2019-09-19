#include "Player.hpp"
const int SHADOW_OFFSET_X = 1;
const int SHADOW_OFFSET_Y = 4;
//
//
//
Player::Player() {
  if (sprite) {
    player_sprite = static_cast<PlayerSprite*>(sprite);
  }
  if (shadow) {
    player_shadow = static_cast<PlayerSprite*>(shadow);
  }
}
//
//
//
void Player::update() {
  sprite->animate();
  shadow->setPosition(sprite->getPosition());
  shadow->move(SHADOW_OFFSET_X, SHADOW_OFFSET_Y);
  shadow->setFrame(sprite->getFrame());
}
