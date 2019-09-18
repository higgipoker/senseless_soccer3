#include "BallSprite.hpp"

//
//
//
BallSprite::BallSprite(const std::string& in_filename,
                       const Engine::SpriteSetDefinition in_def)
    : Engine::Sprite(in_filename) {
  init(in_def);
  setAnimation(&roll_animation);
}
