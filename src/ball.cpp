#include "ball.hpp"
#include "debug.hpp"
#include "globals.hpp"
#include "sprite.hpp"
#include "compass.hpp"
//
// make_ball_sprite
//
int make_ball_sprite(int sprite, const std::string &spritesheet) {
  sf::Texture *tex = acquire_texture(spritesheet);
  sprite_pool[sprite].setTexture(*tex);
  set_sprite_z(sprite_pool[sprite], 3);
  return 0;
}
//
// init_ball
//
int init_ball(Ball &ball) {
  // ball
  int e = acquire_entity();
  ball.entity = e;
  BALL_ENTITY(ball).co_friction = 0.5f;
  BALL_ENTITY(ball).co_bounciness = 0.9f;
  BALL_ENTITY(ball).type = EntityType::Ball;
  ball.spritesheet = Globals::GFX_FOLDER + "playerandball.png";
  BALL_ENTITY(ball).sprite = acquire_sprite(&BALL_ENTITY(ball));
  make_ball_sprite(BALL_ENTITY(ball).sprite, ball.spritesheet);
  entity_pool[e].terminal_velocity = 0.1f;

  // shadow
  init_ball_shadow(ball);
  return 0;
}
//
// init_ball_shadow
//
void init_ball_shadow(Ball &ball) {
  int e = acquire_entity();
  ball.shadow_entity = e;
  BALL_SHADOW_ENTITY(ball).sprite =
      acquire_sprite(&BALL_SHADOW_ENTITY(ball));
  make_ball_sprite(BALL_SHADOW_ENTITY(ball).sprite, ball.spritesheet);
  set_sprite_z(sprite_pool[BALL_SHADOW_ENTITY(ball).sprite], 0);
}
//
// update_ball
//
void update_ball(Ball &ball) {
  BALL_SPRITE(ball).setPosition(BALL_ENTITY(ball).position.x,
                                    BALL_ENTITY(ball).position.y);
  BALL_SHADOW_SPRITE(ball).setPosition(
      BALL_ENTITY(ball).position.x + 2,
      BALL_ENTITY(ball).position.y + 2);

  // perspectivize returns false if ball is behind the camera
  if (perspectivize(BALL_SPRITE(ball), BALL_ENTITY(ball).position.z,
                    ball.collidable.getRadius() * 2, 50)) {
    BALL_SHADOW_SPRITE(ball).setScale(BALL_SPRITE(ball).getScale().x,
                                          BALL_SPRITE(ball).getScale().y);
  } else {
    BALL_SPRITE(ball).setPosition(
        -BALL_SPRITE(ball).getGlobalBounds().left,
        -BALL_SPRITE(ball).getGlobalBounds().top);

    float offset = BALL_ENTITY(ball).velocity.z > 0 ? 0.2f : -0.2f;

    BALL_SHADOW_SPRITE(ball).setScale(
        BALL_SHADOW_SPRITE(ball).getScale().x + offset,
        BALL_SHADOW_SPRITE(ball).getScale().y + offset);
  }
  ball.collidable.setPosition(
      BALL_ENTITY(ball).position.x - ball.collidable.getRadius(),
      BALL_ENTITY(ball).position.y - ball.collidable.getRadius());
  debug_shapes.emplace_back(&ball.collidable);
}
//
// set_animation
//
void start_ball_animation(Ball &ball, BallAnimation id) {
  live_animations[ball.entity] = ball_roll_animations[Direction::WEST];
}
