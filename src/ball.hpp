#pragma once
#include "data.hpp"

#include "globals.hpp"
#include "texture.hpp"

const int BALL_SPRITESHEET_ROWS = 4;
const int BALL_SPRITESHEET_COLS = 2;
const int BALL_SPRITE_FRAMES = BALL_SPRITESHEET_ROWS * BALL_SPRITESHEET_COLS;
const int BALL_SPRITE_WIDTH = 64;
const int BALL_SPRITE_HEIGHT = 64;

static std::vector<sf::IntRect> ball_frames;

/**
 * @brief The Ball struct
 */
struct Ball {
  int entity = 0;
  std::string spritesheet;
  int current_frame = 0;
  bool inited = false;
};

/**
 * @brief get_entity
 * @param ball
 * @return
 */
Entity &get_ball_entity(Ball &ball);

/**
 * @brief get_sprite
 * @param ball
 * @return
 */
sf::Sprite &get_sprite(Ball &ball);

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
 * @brief apply_forces
 * @param ball
 */
void apply_forces(Ball &ball);
