#include "PlayerSprite.hpp"
//
//
//
PlayerSprite::PlayerSprite(std::shared_ptr<sf::Texture> in_texture,
                           const Engine::SpriteSetDefinition in_def)
    : Engine::Sprite(in_texture) {

  init(in_def);

  populateStandAnimations(stand_animations);
  populateRunAnimations(run_animations);
  populateSlideAnimations(slide_animations);

  // for players, anchor the sprite to bottom (position is feet)
  setOrigin(in_def.frame_width / 2, in_def.frame_height);
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
PlayerShadowSprite::PlayerShadowSprite(std::shared_ptr<sf::Texture> in_texture,
                                       const Engine::SpriteSetDefinition in_def)
    : PlayerSprite(in_texture, in_def) {}
