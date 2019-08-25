#pragma once
#include "entity.hpp"
#include "globals.hpp"
#include "texture.hpp"

namespace Ball {

static const int BALL_SPRITESHEET_ROWS = 4;
static const int BALL_SPRITESHEET_COLS = 2;
static const int BALL_SPRITE_FRAMES =
    BALL_SPRITESHEET_ROWS * BALL_SPRITESHEET_COLS;
static const int BALL_SPRITE_WIDTH = 64;
static const int BALL_SPRITE_HEIGHT = 64;

/**
 * @brief The Ball struct
 */
struct Ball {
  Entity::Entity *entity = nullptr;
  Entity::SortableSprite *sprite = nullptr;
  std::string spritesheet;
  int current_frame;
};

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static void populate_ball_sprite_frames(
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

static std::array<sf::IntRect, BALL_SPRITE_FRAMES> ball_frames;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static void make_ball_sprite(Entity::SortableSprite *sprite,
                             const std::string &spritesheet) {
  sf::Texture *tex = Texture::acquire_texture(spritesheet);
  sprite->sprite.setTexture(*tex);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static void init_ball(Ball &ball) {
  Entity::Entity *e = Entity::acquire_entity();
  e->type = Entity::EntityType::Ball;

  ball.entity = e;
  ball.spritesheet = Globals::GFX_FOLDER + "/ball_new.png";
  ball.sprite = Entity::acquire_sprite();
  make_ball_sprite(ball.sprite, ball.spritesheet);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static void apply_forces(Ball &ball) {
    gamelib3::Vector3 tmp(0.01, 0.01);
    ball.entity->velocity *= tmp;
}
}  // namespace Ball
