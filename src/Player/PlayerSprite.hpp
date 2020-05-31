#pragma once

#include <map>

#include "Engine/Compass.hpp"
#include "Engine/Sprite.hpp"
#include "PlayerAnimations.hpp"
namespace Senseless {
enum class TeamStrip;

// sprite frame constants
inline const int VERTICAL_OFFSET_TEAM1 = 0;
inline const int VERTICAL_OFFSET_TEAM2 = 96;
inline const int SHADOW_VERTICAL_OFFSET = 192;
inline const int FRAME_WIDTH = 32;
inline const int FRAME_HEIGHT = 32;
inline const int FRAMES = 72;
inline const int START_ROW = 0;
inline const int START_COL = 0;
inline const int COLS = 24;
inline const int SHADOW_START_ROW = 0;
// ***************************************************************************
// *                                                                         *
// * PlayerSprite                                                            *
// *                                                                         *
// ***************************************************************************
class PlayerSprite : public Sprite {
    public:
    // -----------------------------------------------------------------------
    // functions
    // -----------------------------------------------------------------------
    PlayerSprite        () { perspectivizable = true; };
    PlayerSprite        (   const sf::Texture& in_texture,
                            const TeamStrip in_team,
                            SpriteSetDefinition in_def = SpriteSetDefinition{   VERTICAL_OFFSET_TEAM1,
                                                                                FRAME_WIDTH,
                                                                                FRAME_HEIGHT,
                                                                                FRAMES,
                                                                                START_ROW,
                                                                                START_COL,COLS});
    void  setPlayerAnimation  (PlayerAnimationType in_type, Direction in_direction);
    private:
    AnimMap stand_animations;
    AnimMap run_animations;
    AnimMap slide_animations;
};
// ***************************************************************************
// *                                                                         *
// * PlayerShadowSprite                                                      *
// *                                                                         *
// ***************************************************************************
class PlayerShadowSprite : public PlayerSprite {
    public:
    PlayerShadowSprite(const sf::Texture& in_texture, const SpriteSetDefinition in_def = SpriteSetDefinition{
                            SHADOW_VERTICAL_OFFSET,
                            FRAME_WIDTH,
                            FRAME_HEIGHT,
                            1,
                            SHADOW_START_ROW,
                            START_COL,
                            COLS});
};
}  // namespace Senseless
