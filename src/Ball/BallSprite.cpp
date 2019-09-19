#include "BallSprite.hpp"

//
//
//
BallSprite::BallSprite(std::shared_ptr<sf::Texture> in_texture,
                       const Engine::SpriteSetDefinition in_def)
    : Engine::Sprite(in_texture) {
  init(in_def);
}
//
//
//
BallShadowSprite::BallShadowSprite(std::shared_ptr<sf::Texture> in_texture,
                                   const Engine::SpriteSetDefinition in_def)
    : BallSprite(in_texture, in_def) {}
