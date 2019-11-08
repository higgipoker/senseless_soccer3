#include "BallSprite.hpp"

using namespace Engine;
//
//
//
BallSprite::BallSprite(const sf::Texture &in_texture,
                       const SpriteSetDefinition in_def)
    : Sprite(in_texture) {
  init(in_def);
  setAnimation(&roll_animation);
}
//
//
//
BallShadowSprite::BallShadowSprite(const sf::Texture &in_texture,
                                   const SpriteSetDefinition in_def)
    : BallSprite(in_texture, in_def) {}
