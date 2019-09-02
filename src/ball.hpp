#pragma once
#include "ball_animations.hpp"
#include "data.hpp"
#include "texture.hpp"

#include <SFML/Graphics/CircleShape.hpp>

const int BALL_SPRITESHEET_ROWS = 4;
const int BALL_SPRITESHEET_COLS = 24;
const int BALL_SPRITE_FRAMES = 8;
const int BALL_SPRITE_WIDTH = 32;
const int BALL_SPRITE_HEIGHT = 32;

inline std::vector<sf::IntRect> ball_frames;

#define BallEntity entity_pool[ball.entity]
#define BallShadowEntity entity_pool[ball.shadow_entity]
#define BallSprite sprite_pool[BallEntity.sprite]
#define BALL_SHADOW_SPRITE(B) sprite_pool[BallShadowEntity.sprite]

/**
 * @brief The Ball struct
 */
struct Ball {
  int entity = -1;
  int shadow_entity = -1;
  int current_frame = 0;
  bool inited = false;
  sf::CircleShape collidable{3.f, 10};
};
/**
 * @brief make_ball_sprite
 * @param sprite
 * @param spritesheet
 * @return
 */
int make_ball_sprite(int sprite, const std::string &spritesheet);
/**
 * @brief init_ball
 * @param ball
 * @return
 */
int init_ball(Ball &ball);
/**
 * @brief init_ball_shadow
 * @param ball
 */
void init_ball_shadow(Ball &ball);
/**
 * @brief update_ball
 * @param ball
 */
void update_ball(Ball &ball);
/**
 * @brief start_ball_animation
 * @param player
 * @param id
 */
void start_ball_animation(Ball &ball, BallAnimation id);
