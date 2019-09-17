#include "PlayerSprite.hpp"
//
//
//
PlayerSprite::PlayerSprite(const std::string& in_filename)
    : Engine::Sprite(in_filename) {
  Engine::SpriteSetDefinition def;
  def.spritesheet = in_filename;
  def.frame_width = 32;
  def.frame_height = 32;
  def.spriteset_frames = 72;
  def.start_row = 0;
  def.start_col = 0;
  def.sheet_cols = 24;

  init(def);

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
