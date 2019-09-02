#include "player.hpp"
#include "debug.hpp"
#include "globals.hpp"
#include "physics.hpp"
//
//
//
void make_player_sprite(int sprite, const std::string &spritesheet) {
  sf::Texture *tex = acquire_texture(spritesheet);
  sprite_pool[sprite].setTexture(*tex);
}
//
//
//
void init_player(Player &p) {
  int e = acquire_entity();

  if (e == -1) {
    std::cout << "no entity" << std::endl;
    return;
  }

  entity_pool[e].type = EntityType::Player;
  p.shirt_number = 1;
  p.entity = e;
  p.spritesheet = Globals::GFX_FOLDER + "playerandball.png";

  int s = acquire_sprite(&entity_pool[e]);
  if (s == -1) {
    std::cout << "no sprite" << std::endl;
    release_entity(e);
    return;
  }
  p.facing.direction = Direction::SOUTH;
  entity_pool[e].sprite = s;
  entity_pool[e].co_friction = 25.f;  // direct control
  entity_pool[e].co_air_resistance = 0;
  entity_pool[e].terminal_velocity = 0.03f;
  entity_pool[e].position.y = PLAYER_SPRITE_HEIGHT;
  entity_pool[e].speed = 100;
  make_player_sprite(entity_pool[e].sprite, p.spritesheet);
  set_sprite_z(sprite_pool[entity_pool[e].sprite], (rand() % 50) + 5);
  PLAYER_SPRITE(p).setOrigin(PLAYER_SPRITE_WIDTH / 2, PLAYER_SPRITE_HEIGHT);
  init_player_shadow(p);
}
//
//
//
void init_player_shadow(Player &player) {
  int e = acquire_entity();
  player.shadow_entity = e;
  PLAYER_SHADOW_ENTITY(player).sprite =
      acquire_sprite(&PLAYER_SHADOW_ENTITY(player));
  make_player_sprite(PLAYER_SHADOW_ENTITY(player).sprite, player.spritesheet);
  set_sprite_z(sprite_pool[PLAYER_SHADOW_ENTITY(player).sprite], 1);
}
//
//
//
void release_players(std::vector<Player> &players) {
  for (auto &player : players) {
    release_texture(player.spritesheet);
    release_sprite(entity_pool[player.entity].sprite);
    release_entity(player.entity);

    // shadow
    release_sprite(entity_pool[player.shadow_entity].sprite);
    release_entity(player.shadow_entity);
  }
}
//
//
//
void think(Player &player) {}
//
//
//
void start_player_animation(Player &player, PlayerAnimationType type,
                            Direction dir) {
  switch (type) {
    case PlayerAnimationType::Stand:
      live_animations[player.entity] = player_stand_animations[dir];
      break;
    case PlayerAnimationType::Run:
      live_animations[player.entity] = player_run_animations[dir];
      break;
  }
}
//
//
//
void stop_animation(Player &player) { live_animations.erase(player.entity); }
//
//
//
void change_player_state(Player &player, PlayerState new_state) {
  player.facing = Direction::NONE;
  player.state = new_state;
  switch (new_state) {
    case PlayerState::Stand:
      break;
    case PlayerState::Run:
      break;
  }
}
//
//
//
void do_stand_state(Player &player, Ball &ball) {
  // update direction
  Compass to_ball;
  to_ball.direction = direction_to(PLAYER_ENTITY(player), BallEntity);
  player.facing = to_ball.direction;

  start_player_animation(player, PlayerAnimationType::Stand,
                         player.facing.direction);

  if (Floats::greater_than(PLAYER_ENTITY(player).velocity.magnitude2d(), 0)) {
    change_player_state(player, PlayerState::Run);
  }
}
//
//
//
void do_run_state(Player &player, Ball &ball) {
  // update direction
  player.facing.fromVector(PLAYER_ENTITY(player).velocity.normalise());
  if (player.old_direction != player.facing) {
    start_player_animation(player, PlayerAnimationType::Run,
                           player.facing.direction);
  }
  if (Floats::equal(PLAYER_ENTITY(player).velocity.magnitude2d(), 0)) {
    change_player_state(player, PlayerState::Stand);
  }
}
//
//
//
void update_player(Player &player, Ball &ball) {
  // player's can't exert a force whilst in the air!
  if (Floats::greater_than(PLAYER_ENTITY(player).position.z, 0)) {
    PLAYER_ENTITY(player).force.reset();
  }

  // update player sprite and shadow
  PLAYER_SPRITE(player).setPosition(PLAYER_ENTITY(player).position.x,
                                    PLAYER_ENTITY(player).position.y);
  PLAYER_SHADOW_SPRITE(player).setPosition(
      PLAYER_ENTITY(player).position.x + 2,
      PLAYER_ENTITY(player).position.y + 2);

  // if perspectivize reutrns false then the sprite is behind the camera
  if (perspectivize(PLAYER_SPRITE(player), PLAYER_ENTITY(player).position.z,
                    PLAYER_SPRITE(player).getLocalBounds().width, 50)) {
    PLAYER_SHADOW_SPRITE(player).setScale(PLAYER_SPRITE(player).getScale().x,
                                          PLAYER_SPRITE(player).getScale().y);
  } else {
    PLAYER_SPRITE(player).setPosition(
        -PLAYER_SPRITE(player).getGlobalBounds().left,
        -PLAYER_SPRITE(player).getGlobalBounds().top);

    PLAYER_SHADOW_SPRITE(player).setScale(
        PLAYER_SHADOW_SPRITE(player).getScale().x,
        PLAYER_SHADOW_SPRITE(player).getScale().y);
  }

  // updat feet (collidable shape for kicking)
  player.feet.setPosition(
      PLAYER_ENTITY(player).position.x - player.feet.getRadius(),
      PLAYER_ENTITY(player).position.y - player.feet.getRadius());
  player.control.setPosition(
      PLAYER_ENTITY(player).position.x - player.control.getRadius(),
      PLAYER_ENTITY(player).position.y - player.control.getRadius());

  debug_shapes.emplace_back(&player.feet);
  debug_shapes.emplace_back(&player.control);

  // state machine
  switch (player.state) {
    case PlayerState::Stand:
      do_stand_state(player, ball);
      break;
    case PlayerState::Run:
      do_run_state(player, ball);
      break;
  }
  player.changed_direction = false;
  if (player.old_direction != player.facing) {
    player.changed_direction = true;
    std::cout << "changed direction" << std::endl;
    // check for close control

    if (contains(player.control, ball.collidable)) {
      std::cout << "close control" << std::endl;
      Vector3 f(player.feet.getPosition().x, player.feet.getPosition().y);
      Vector3 ball_pos = f + (player.facing.toVector() * 7);

      BallEntity.velocity.reset();

      // set new position
      BallEntity.position = ball_pos;
    }
  }
  player.old_direction = player.facing;

  // check for ball collision
  if (collides(player.feet, ball.collidable)) {
    Vector3 force = player.facing.toVector();
    force *= 7000;
    BallEntity.velocity.reset();
    apply_force(BallEntity, force);
  }
}
//
//
//
void update_players(std::vector<Player> &players, Ball &ball) {
  for (auto &player : players) {
    update_player(player, ball);
  }
}
