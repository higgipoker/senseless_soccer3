#include "ball.hpp"

// -----------------------------------------------------------------------------
// get_sprite
// -----------------------------------------------------------------------------
sf::Sprite &get_sprite(Ball &ball) {
  return sprite_pool[get_entity(ball).sprite];
}

// -----------------------------------------------------------------------------
// get_entity
// -----------------------------------------------------------------------------
Entity &get_entity(Ball &ball) { return entity_pool[ball.entity]; }

// -----------------------------------------------------------------------------
// make_ball_sprite
// -----------------------------------------------------------------------------
int make_ball_sprite(int sprite, const std::string &spritesheet) {
  sf::Texture *tex = acquire_texture(spritesheet);
  sprite_pool[sprite].setTexture(*tex);
  set_sprite_z(sprite_pool[sprite], 3);
  return 0;
}

// -----------------------------------------------------------------------------
// init_ball
// -----------------------------------------------------------------------------
int init_ball(Ball &ball) {
  int e = acquire_entity();
  ball.entity = e;
  get_entity(ball).type = EntityType::Ball;
  ball.spritesheet = Globals::GFX_FOLDER + "/ball_new.png";
  get_entity(ball).sprite = acquire_sprite(&get_entity(ball));
  make_ball_sprite(get_entity(ball).sprite, ball.spritesheet);
  return 0;
}

// -----------------------------------------------------------------------------
// apply_forces
// -----------------------------------------------------------------------------
void apply_forces(Ball &ball) {}
