#include "ball.hpp"
#include "compass.hpp"
#include "debug.hpp"
#include "globals.hpp"
#include "sprite.hpp"

static const int BALL_SHADOW_OFFSET = 2;

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
  BallEntity.co_friction = 0.01f;
  BallEntity.co_bounciness = 0.7f;
  BallEntity.mass = 3.5f;
  BallEntity.type = EntityType::Ball;
  BallEntity.sprite = acquire_sprite(&BallEntity);
  BallSprite.spritesheet = Globals::GFX_FOLDER + "playerandball.png";
  make_ball_sprite(BallEntity.sprite, BallSprite.spritesheet);
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
  BallShadowEntity.sprite = acquire_sprite(&BallShadowEntity);
  make_ball_sprite(BallShadowEntity.sprite, BallSprite.spritesheet);
  set_sprite_z(sprite_pool[BallShadowEntity.sprite], Globals::SHADOW_Z);
}
//
// update_ball
//
void update_ball(Ball &ball) {
  BallSprite.setPosition(BallEntity.position.x, BallEntity.position.y);
  BallShadowSPrite.setPosition(BallEntity.position.x + 2,
                               BallEntity.position.y + 2);

  // perspectivize returns false if ball is behind the camera
  if (perspectivize(BallSprite, BallEntity.position.z,
                    ball.collidable.getRadius() * 2, 50)) {
    BallShadowSPrite.setScale(BallSprite.getScale().x, BallSprite.getScale().y);
  } else {
    BallSprite.setScale(0, 0);

    float offset =
        Floats::greater_than(BallEntity.velocity.z, 0) ? 0.2f : -0.2f;

//    BallShadowSPrite.setScale(BallShadowSPrite.getScale().x /*+ offset*/,
//                              BallShadowSPrite.getScale().y /*+ offset*/);

    BallShadowSPrite.setScale(100,
                              100);
  }
  ball.collidable.setPosition(
      BallEntity.position.x - ball.collidable.getRadius(),
      BallEntity.position.y - ball.collidable.getRadius());
  debug_shapes.emplace_back(&ball.collidable);
}
//
// set_animation
//
void start_ball_animation(Ball &ball, BallAnimation id) {
  live_animations[ball.entity] = ball_roll_animations[Direction::WEST];
}
