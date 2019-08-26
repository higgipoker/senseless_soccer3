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
  // give a nice interface to ball stuff -> these are just aliases
  sf::Sprite &Sprite() {
    return Data::sprite_pool[Data::entity_pool[entity].sprite];
  }
  Data::Entity &Entity() { return Data::entity_pool[entity]; }

  int entity = 0;
  std::string spritesheet;
  int current_frame = 0;
  bool inited = false;
};

// -----------------------------------------------------------------------------
// populate_ball_sprite_frames
// -----------------------------------------------------------------------------
inline void populate_ball_sprite_frames(
    std::array<sf::IntRect, BALL_SPRITE_FRAMES> &frames) {
  int x = 0;
  int y = 0;
  int row = 0;
  int col = 0;
  for (auto &rect : frames) {
    rect.left = x;
    rect.top = y;
    rect.width = BALL_SPRITE_WIDTH;
    rect.height = BALL_SPRITE_HEIGHT;

    x += BALL_SPRITE_WIDTH;

    if (++col == BALL_SPRITESHEET_COLS) {
      x = 0;
      y += BALL_SPRITE_HEIGHT;
      col = 0;
    }
  }
}

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

  Data::entity_pool[e].type = Data::EntityType::Ball;

  ball.entity = e;
  ball.spritesheet = Globals::GFX_FOLDER + "/ball_new.png";
  Data::entity_pool[e].sprite = Data::acquire_sprite(&Data::entity_pool[e]);
  if (Data::entity_pool[e].sprite == -1) {
    Data::release_entity(e);
    return -1;
  }
  make_ball_sprite(Data::entity_pool[e].sprite, ball.spritesheet);
  return 0;
}

// -----------------------------------------------------------------------------
// apply_forces
// -----------------------------------------------------------------------------
inline void apply_forces(Ball &ball) {}
}  // namespace Ball
