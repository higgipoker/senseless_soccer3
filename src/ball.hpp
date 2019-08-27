#pragma once
#include "data.hpp"

#include "globals.hpp"
#include "texture.hpp"

namespace Ball {

inline const int BALL_SPRITESHEET_ROWS = 4;
inline const int BALL_SPRITESHEET_COLS = 2;
inline const int BALL_SPRITE_FRAMES =
    BALL_SPRITESHEET_ROWS * BALL_SPRITESHEET_COLS;
inline const int BALL_SPRITE_WIDTH = 64;
inline const int BALL_SPRITE_HEIGHT = 64;

inline std::array<sf::IntRect, BALL_SPRITE_FRAMES> ball_frames;

/**
 * @brief The Ball struct
 */
struct Ball {
  int entity = 0;
  std::string spritesheet;
  int current_frame = 0;
  bool inited = false;
};

inline Data::Entity &get_entity(Ball &ball) {
  return Data::entity_pool[ball.entity];
}

inline sf::Sprite &get_sprite(Ball &ball) {
  return Data::sprite_pool[get_entity(ball).sprite];
}

/**
 * @brief populate_ball_sprite_frames
 * @param frames
 */
void populate_ball_sprite_frames(
    std::array<sf::IntRect, BALL_SPRITE_FRAMES> &frames);

// -----------------------------------------------------------------------------
// make_ball_sprite
// -----------------------------------------------------------------------------
inline int make_ball_sprite(int sprite, const std::string &spritesheet) {
  sf::Texture *tex = Texture::acquire_texture(spritesheet);
  Data::sprite_pool[sprite].setTexture(*tex);
  Data::sprite_pool[sprite].set_z(3);
  return 0;
}

// -----------------------------------------------------------------------------
// init_ball
// -----------------------------------------------------------------------------
inline int init_ball(Ball &ball) {
  int e = Data::acquire_entity();
  if (e == -1) {
    return -1;
  }

  ball.entity = e;
  get_entity(ball).type = Data::EntityType::Ball;
  ball.spritesheet = Globals::GFX_FOLDER + "/ball_new.png";
  get_entity(ball).sprite = Data::acquire_sprite(&get_entity(ball));
  if (get_entity(ball).sprite == -1) {
    Data::release_entity(e);
    return -1;
  }
  make_ball_sprite(get_entity(ball).sprite, ball.spritesheet);
  return 0;
}

// -----------------------------------------------------------------------------
// apply_forces
// -----------------------------------------------------------------------------
inline void apply_forces(Ball &ball) {}
}  // namespace Ball
