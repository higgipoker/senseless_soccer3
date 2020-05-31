#include "PlayerSprite.hpp"
//
#include "Team/Team.hpp"
//
//
//
namespace Senseless {
//
//
//
PlayerSprite::PlayerSprite(const sf::Texture& in_texture, const TeamStrip in_team,
                           SpriteSetDefinition in_def)
    : Sprite(in_texture) {
  perspectivizable = true;

  if (in_team == TeamStrip::Away) {
    in_def.vertical_offset = VERTICAL_OFFSET_TEAM2;
  }

  init(in_def);

  populateStandAnimations(stand_animations);
  populateRunAnimations(run_animations);
  populateSlideAnimations(slide_animations);

  // for players, anchor the sprite to bottom (position is feet)
  setOrigin(static_cast<float>(in_def.frame_width / 2), static_cast<float>(in_def.frame_height));
}
//
//
//
void PlayerSprite::setPlayerAnimation(PlayerAnimationType in_type, Direction in_direction) {
  switch (in_type) {
    case PlayerAnimationType::Run:
      Sprite::setAnimation(&(run_animations.at(in_direction)));
      break;
    case PlayerAnimationType::Stand:
      Sprite::setAnimation(&(stand_animations.at(in_direction)));
      break;
    case PlayerAnimationType::Slide:
      Sprite::setAnimation(&(slide_animations.at(in_direction)));
      break;
  }
}
//
//
//
PlayerShadowSprite::PlayerShadowSprite(const sf::Texture& in_texture,
                                       const SpriteSetDefinition in_def)
    : PlayerSprite(in_texture, TeamStrip::Home, in_def) {
  perspectivizable = false;
}
}  // namespace Senseless
