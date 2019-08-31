#include "ball.hpp"
#include "debug.hpp"
#include "globals.hpp"
#include "sprite.hpp"

// -----------------------------------------------------------------------------
// get_ball_sprite
// -----------------------------------------------------------------------------
sf::Sprite &get_ball_sprite(Ball &ball) {
  return sprite_pool[get_ball_entity(ball).sprite];
}
// -----------------------------------------------------------------------------
// get_ball_shadow_sprite
// -----------------------------------------------------------------------------
sf::Sprite &get_ball_shadow_sprite(Ball &ball) {
  return sprite_pool[get_ball_shadow_entity(ball).sprite];
}

// -----------------------------------------------------------------------------
// get_entity
// -----------------------------------------------------------------------------
Entity &get_ball_entity(Ball &ball) { return entity_pool[ball.entity]; }
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Entity &get_ball_shadow_entity(Ball &ball) {
  return entity_pool[ball.shadow_entity];
}

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
  // ball
  int e = acquire_entity();
  ball.entity = e;
  get_ball_entity(ball).co_friction = 0.1f;
  get_ball_entity(ball).co_bounciness = 0.7f;
  get_ball_entity(ball).type = EntityType::Ball;
  ball.spritesheet = Globals::GFX_FOLDER + "playerandball.png";
  get_ball_entity(ball).sprite = acquire_sprite(&get_ball_entity(ball));
  make_ball_sprite(get_ball_entity(ball).sprite, ball.spritesheet);
  entity_pool[e].terminal_velocity = 0.1f;

  // shadow
  init_ball_shadow(ball);
  return 0;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void init_ball_shadow(Ball &ball) {
  int e = acquire_entity();
  ball.shadow_entity = e;
  get_ball_shadow_entity(ball).sprite =
      acquire_sprite(&get_ball_shadow_entity(ball));
  make_ball_sprite(get_ball_shadow_entity(ball).sprite, ball.spritesheet);
  set_sprite_z(sprite_pool[get_ball_shadow_entity(ball).sprite], 0);
}

// -----------------------------------------------------------------------------
// update_ball
// -----------------------------------------------------------------------------
void update_ball(Ball &ball) {
  get_ball_sprite(ball).setPosition(get_ball_entity(ball).position.x,
                                    get_ball_entity(ball).position.y);
  get_ball_shadow_sprite(ball).setPosition(
      get_ball_entity(ball).position.x + 2,
      get_ball_entity(ball).position.y + 2);

  if (!perspectivize(get_ball_sprite(ball), get_ball_entity(ball).position.z,
                     ball.collidable.getRadius() * 2, 50)) {
    get_ball_sprite(ball).setPosition(
        -get_ball_sprite(ball).getGlobalBounds().left,
        -get_ball_sprite(ball).getGlobalBounds().top);

    float offset = get_ball_entity(ball).velocity.z > 0 ? 0.2f : -0.2f;

    get_ball_shadow_sprite(ball).setScale(
        get_ball_shadow_sprite(ball).getScale().x + offset,
        get_ball_shadow_sprite(ball).getScale().y + offset);
  } else {
    get_ball_shadow_sprite(ball).setScale(get_ball_sprite(ball).getScale().x,
                                          get_ball_sprite(ball).getScale().y);
  }
  debug_shapes.emplace_back(&ball.collidable);
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
