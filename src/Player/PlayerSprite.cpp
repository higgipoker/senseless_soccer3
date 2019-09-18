#include "PlayerSprite.hpp"
//
//
//
PlayerSprite::PlayerSprite(const std::string& in_filename,
                           const Engine::SpriteSetDefinition in_def)
    : Engine::Sprite(in_filename) {

  init(in_def);

  populateStandAnimations(stand_animations);
  populateRunAnimations(run_animations);
  populateSlideAnimations(slide_animations);
}
//
//
//
void PlayerSprite::setAnimation(PlayerAnimationType in_type,
                                Engine::Direction in_direction) {
  switch (in_type) {
    case PlayerAnimationType::Run:
      Engine::Sprite::setAnimation(&(run_animations.at(in_direction)));
      break;
    case PlayerAnimationType::Stand:
      Engine::Sprite::setAnimation(&(stand_animations.at(in_direction)));
      break;
    case PlayerAnimationType::Slide:
      Engine::Sprite::setAnimation(&(slide_animations.at(in_direction)));
      break;
  }
}
//
//
//
PlayerShadowSprite::PlayerShadowSprite(const std::string& in_filename,
                                       const Engine::SpriteSetDefinition in_def)
    : PlayerSprite(in_filename, in_def) {}
