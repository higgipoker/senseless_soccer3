#include "BallSprite.hpp"

using namespace Engine;
//
//
//
BallSprite::BallSprite(std::shared_ptr<sf::Texture> in_texture,
                       const SpriteSetDefinition in_def)
    : Sprite(in_texture) {
  init(in_def);
}
//
//
//
BallShadowSprite::BallShadowSprite(std::shared_ptr<sf::Texture> in_texture,
                                   const SpriteSetDefinition in_def)
    : BallSprite(in_texture, in_def) {}
