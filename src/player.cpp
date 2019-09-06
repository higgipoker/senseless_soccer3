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
void init_player(Player &player) {
  int e = acquire_entity();

  if (e == -1) {
    std::cout << "no entity" << std::endl;
    return;
  }

  entity_pool[e].type = EntityType::Player;
  player.entity = e;

  int s = acquire_sprite(&entity_pool[e]);
  if (s == -1) {
    std::cout << "no sprite" << std::endl;
    release_entity(e);
    return;
  }
  player.facing.direction = Direction::SOUTH;
  entity_pool[e].sprite = s;
  entity_pool[e].co_friction = 0.0f;  // direct control
  entity_pool[e].co_air_resistance = 0;
  entity_pool[e].terminal_velocity = 0.03f;
  entity_pool[e].position.y = PLAYER_SPRITE_HEIGHT;
  entity_pool[e].speed = 100;
  entity_pool[e].mass = 3;
  PlayerSprite.spritesheet = Globals::GFX_FOLDER + "playerandball.png";
  make_player_sprite(entity_pool[e].sprite, PlayerSprite.spritesheet);
  set_sprite_z(sprite_pool[entity_pool[e].sprite], (rand() % 50) + 5);
  PlayerSprite.setOrigin(PLAYER_SPRITE_WIDTH / 2, PLAYER_SPRITE_HEIGHT);
  init_player_shadow(player);
  player.control.setOutlineThickness(2);
  player.control.setFillColor(sf::Color(0, 0, 0, 0));
  player.control.setOutlineColor(sf::Color::Red);
}
//
//
//
void init_player_shadow(Player &player) {
  int e = acquire_entity();
  player.shadow_entity = e;
  PlayerShadowEntity.sprite = acquire_sprite(&PlayerShadowEntity);
  make_player_sprite(PlayerShadowEntity.sprite, PlayerSprite.spritesheet);
  set_sprite_z(sprite_pool[PlayerShadowEntity.sprite], 1);
}
//
//
//
void release_players(std::vector<Player> &players) {
  for (auto &player : players) {
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
  player.state = new_state;
  switch (new_state) {
    case PlayerState::Stand:
      break;
    case PlayerState::Run:
      // to force change animation even if no change direction
      player.facing = Direction::NONE;
      break;
  }
}
//
//
//
void do_stand_state(Player &player, Ball &ball) {
  // set facing to direction to ball
  Compass to_ball;
  to_ball.direction = direction_to(PlayerEntity, BallEntity);
  player.facing = to_ball.direction;

  // start animation depending on facing direction (look at ball)
  if (player.facing.direction == Direction::WEST) {
    int b = 1;
  }
  if (player.shirt_number == 1) {
    std::cout << player.facing.print() << std::endl;
  }
  start_player_animation(player, PlayerAnimationType::Stand,
                         player.facing.direction);

  if (contains(player.control, ball.collidable)) {
    player.control.setOutlineColor(sf::Color::Green);
  }
  // change state?
  if (Floats::greater_than(PlayerEntity.velocity.magnitude2d(), 0)) {
    change_player_state(player, PlayerState::Run);
  }
}
//
//
//
void do_run_state(Player &player, Ball &ball) {
  // set facing to direction of movement
  player.facing.fromVector(PlayerEntity.velocity.normalise());

  // set animation depending on facing direction
  if (player.old_direction != player.facing) {
    start_player_animation(player, PlayerAnimationType::Run,
                           player.facing.direction);
  }
  // check for ball collision (dribble)
  if (collides(player.feet, ball.collidable)) {
    do_dribble(player, ball);
  }

  // check for close control (turned with ball)
  if (contains(player.control, ball.collidable)) {
    player.control.setOutlineColor(sf::Color::Green);
    if (player.changed_direction && player.ball_under_control) {
      do_close_control(player, ball);
    }
  } else {
    player.ball_under_control = false;
  }
  // change state?
  if (Floats::equal(PlayerEntity.velocity.magnitude2d(), 0)) {
    change_player_state(player, PlayerState::Stand);
  }
}
//
//
//
void update_player(Player &player, Ball &ball) {
  player.control.setOutlineColor(sf::Color::Red);

  PlayerEntity.velocity.x = PlayerEntity.velocity.y = 0;
  if (Floats::greater_than(PlayerEntity.force.x, 0)) {
    PlayerEntity.velocity.x =  1;
  }
  if (Floats::less_than(PlayerEntity.force.x, 0)) {
    PlayerEntity.velocity.x = -1;
  }
  if (Floats::greater_than(PlayerEntity.force.y, 0)) {
    PlayerEntity.velocity.y =  1;
  }
  if (Floats::less_than(PlayerEntity.force.y, 0)) {
    PlayerEntity.velocity.y =  -1;
  }

  if (Floats::greater_than(PlayerEntity.velocity.magnitude(), 0)) {
    auto mag = PlayerEntity.velocity.magnitude2d();
    PlayerEntity.velocity = PlayerEntity.velocity.normalise2d();
    PlayerEntity.velocity.x *= mag * PlayerEntity.speed; 
    PlayerEntity.velocity.y *= mag * PlayerEntity.speed;
    }

  // player's can't exert a force whilst in the air!
  if (Floats::greater_than(PlayerEntity.position.z, 0)) {
    PlayerEntity.force.reset();
  }

  // update player sprite and shadow
  PlayerSprite.setPosition(PlayerEntity.position.x, PlayerEntity.position.y);
  PlayerShadowSprite.setPosition(PlayerEntity.position.x + 2,
                                 PlayerEntity.position.y + 2);

  // if perspectivize reutrns false then the sprite is behind the camera
  if (perspectivize(PlayerSprite, PlayerEntity.position.z,
                    PlayerSprite.getLocalBounds().width, 50)) {
    PlayerShadowSprite.setScale(PlayerSprite.getScale().x,
                                PlayerSprite.getScale().y);
  } else {
    PlayerSprite.setPosition(-PlayerSprite.getGlobalBounds().left,
                             -PlayerSprite.getGlobalBounds().top);

    PlayerShadowSprite.setScale(PlayerShadowSprite.getScale().x,
                                PlayerShadowSprite.getScale().y);
  }

  // updat feet (collidable shape for kicking)
  player.feet.setPosition(PlayerEntity.position.x - player.feet.getRadius(),
                          PlayerEntity.position.y - player.feet.getRadius());
  player.control.setPosition(
      PlayerEntity.position.x - player.control.getRadius(),
      PlayerEntity.position.y - player.control.getRadius());

  debug_shapes.emplace_back(&player.feet);
  debug_shapes.emplace_back(&player.control);

  player.changed_direction = false;
  if (player.old_direction != player.facing) {
    player.changed_direction = true;
  }
  player.old_direction = player.facing;

  // state machine
  switch (player.state) {
    case PlayerState::Stand:
      do_stand_state(player, ball);
      break;
    case PlayerState::Run:
      do_run_state(player, ball);
      break;
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
//
//
//
void do_close_control(Player &player, Ball &ball) {
  Vector3 f(player.feet.getPosition().x, player.feet.getPosition().y);
  Vector3 ball_pos = f + (player.facing.toVector() * 6);
  BallEntity.force.reset();
  BallEntity.velocity.reset();
  BallEntity.position = ball_pos;
}
//
//
//
void do_dribble(Player &player, Ball &ball) {
  player.ball_under_control = true;
  Vector3 force = player.facing.toVector();
  force *= 6000;
  BallEntity.velocity.reset();
  apply_force(BallEntity, force);
}
