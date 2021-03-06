#pragma once

#include <map>

#include "Engine/Compass.hpp"
#include "Engine/Sprite.hpp"
#include "Engine/SpriteAnimation.hpp"
#include <memory>
namespace Senseless {
static const int BALL_ANIM_FRAME_TIME = 6;
//
// spritesheet layout defines
//
inline const int DEFAULT_VERTICAL_OFFSET = 224;
inline const int BALL_FRAME_WIDTH = 32;
inline const int BALL_FRAME_HEIGHT = 32;
inline const int BALL_FRAMES = 7;
inline const int BALL_START_ROW = 0;
inline const int BALL_START_COL = 0;
inline const int BALL_COLS = 8;
inline const int BALL_SHADOW_FRAMES = 1;
inline const int BALL_SHADOW_START_COL = 7;
//
// rolling animation
//
inline std::vector<int> roll{0, 1, 2, 3, 4, 5, 6};
//
// anim ids
//
enum {
  ID_ANIM_ROLL = 1,
};
// ***************************************************************************
// *                                                                         *
// * BallSprite                                                              *
// *                                                                         *
// ***************************************************************************
class BallSprite : public Sprite {
 public:

    BallSprite  (   const sf::Texture& in_texture,
                    const SpriteSetDefinition in_def = SpriteSetDefinition{
                    DEFAULT_VERTICAL_OFFSET,
                    BALL_FRAME_WIDTH,
                    BALL_FRAME_HEIGHT,
                    BALL_FRAMES,
                    BALL_START_ROW,
                    BALL_START_COL,
                    BALL_COLS});

    protected:
    SpriteAnimation roll_animation{ID_ANIM_ROLL, BALL_ANIM_FRAME_TIME, roll};
};
// ***************************************************************************
// *                                                                         *
// * BallShadowSprite                                                        *
// *                                                                         *
// ***************************************************************************
class BallShadowSprite : public Sprite {
    public:
    BallShadowSprite(   const sf::Texture& in_texture,
                        const SpriteSetDefinition in_def = SpriteSetDefinition{
                        DEFAULT_VERTICAL_OFFSET,
                        BALL_FRAME_WIDTH,
                        BALL_FRAME_HEIGHT,
                        BALL_SHADOW_FRAMES,
                        BALL_START_ROW,
                        BALL_SHADOW_START_COL,
                        BALL_COLS});
};
}  // namespace Senseless
