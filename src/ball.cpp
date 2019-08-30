#include "ball.hpp"
#include "sprite.hpp"

// -----------------------------------------------------------------------------
// get_sprite
// -----------------------------------------------------------------------------
sf::Sprite &get_sprite(Ball &ball) {
  return sprite_pool[get_ball_entity(ball).sprite];
}

// -----------------------------------------------------------------------------
// get_entity
// -----------------------------------------------------------------------------
Entity &get_ball_entity(Ball &ball) { return entity_pool[ball.entity]; }

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
  get_ball_entity(ball).co_friction = 0.01f;
  get_ball_entity(ball).type = EntityType::Ball;
  ball.spritesheet = Globals::GFX_FOLDER + "playerandball.png";
  get_ball_entity(ball).sprite = acquire_sprite(&get_ball_entity(ball));
  make_ball_sprite(get_ball_entity(ball).sprite, ball.spritesheet);
  entity_pool[e].terminal_velocity = 0.1f;
  return 0;
}

// -----------------------------------------------------------------------------
// update_ball
// -----------------------------------------------------------------------------
void update_ball(Ball &ball) {
  get_sprite(ball).setPosition(get_ball_entity(ball).position.x,
                               get_ball_entity(ball).position.y);
  perspectivize(get_sprite(ball), get_ball_entity(ball).position.z, 3, 20);
}

// -----------------------------------------------------------------------------
// set_animation
// -----------------------------------------------------------------------------
void start_ball_animation(Ball &ball, BallAnimation id) {
  Animation anim;
  anim.type = EntityType::Ball;
  load_ball_animation_frames(anim, id);
  live_animations.insert(std::make_pair(ball.entity, anim));
}
