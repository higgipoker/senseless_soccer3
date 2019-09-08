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
  player.entity = acquire_entity();

  if (player.entity == -1) {
    std::cout << "no entity" << std::endl;
    exit(EXIT_FAILURE);
  }

  // all the entity parameters
  PlayerEntity.type = EntityType::Player;
  PlayerEntity.speed = 5.0f;
  PlayerEntity.terminal_velocity = 1;
  PlayerEntity.co_friction = 1.0f;
  PlayerEntity.co_bounciness = 0.0f;
  PlayerEntity.co_air_resistance = 0.0f;
  PlayerEntity.mass = 20;
  PlayerEntity.position.y = PLAYER_SPRITE_HEIGHT;

  // the player paramaters
  player.feet.setRadius(3.5f);
  player.control.setRadius(16.0f);

  // set up the sprite
  PlayerEntity.sprite = acquire_sprite(&PlayerEntity);
  if (PlayerEntity.sprite == -1) {
    std::cout << "no sprite" << std::endl;
    release_entity(player.entity);
    exit(EXIT_FAILURE);
  }

  // sprite stuff
  PlayerSprite.spritesheet = Globals::GFX_FOLDER + "playerandball.png";
  make_player_sprite(PlayerEntity.sprite, PlayerSprite.spritesheet);
  set_sprite_z(sprite_pool[PlayerEntity.sprite], (rand() % 50) + 5);
  PlayerSprite.setOrigin(PLAYER_SPRITE_WIDTH / 2, PLAYER_SPRITE_HEIGHT);
  init_player_shadow(player);

  // player specific stuff
  player.facing.direction = Direction::SOUTH;
  player.control.setOutlineThickness(2);
  player.control.setFillColor(sf::Color::Transparent);
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
    player.consecutive_dribble_turns = 0;
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
  player.feet.setFillColor(sf::Color::White);

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
  if (player.consecutive_dribble_turns++ > 3) {
    return;
  }
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
  player.feet.setFillColor(sf::Color::Green);
  player.ball_under_control = true;
  Vector3 force = player.facing.toVector();
  float p = 5.f;
  // normalize
  auto mag = force.magnitude2d();
  force = force.normalise2d();
  force.x *= mag * p;
  force.y *= mag * p;
  BallEntity.velocity.reset();
  apply_force(BallEntity, force);
}
//
//
//
void kick(Player &player, float power) {
  std::cout << "kick" << std::endl;
  Vector3 force = player.facing.toVector();

  // normalize
  float mag = force.magnitude2d();
  force = force.normalise2d();
  force.x *= mag * power;
  force.y *= mag * power;
  force.z = 0;

  entity_pool[Globals::ball->entity].velocity.reset();
  apply_force(entity_pool[Globals::ball->entity], force);
}
//
//
//
void handle_player_inputs(std::set<Gamepad *> gamepads) {
  // for each gamepad
  for (auto &gamepad : gamepads) {
    if (!gamepad->device.cb.player) continue;
    // for each callback
    for (auto &event : gamepad->device.cb.events) {
      Entity &player = entity_pool[gamepad->device.cb.player->entity];
      switch (event) {
        case ControllerEventID::Fire:
          kick(*gamepad->device.cb.player);
          break;
        case ControllerEventID::DPadRight:
          apply_force(player, Vector3(1, 0));
          break;
        case ControllerEventID::DPadLeft:
          apply_force(player, Vector3(-1, 0));
          break;
        case ControllerEventID::DPadUp:
          apply_force(player, Vector3(0, -1));
          break;
        case ControllerEventID::DPadDown:
          apply_force(player, Vector3(0, 1));
          break;
        case ControllerEventID::FireTap:
          kick(*gamepad->device.cb.player, 10);
          break;
        case ControllerEventID::FiredoubleTap:
          break;
        case ControllerEventID::NoEvent:
          break;
      }
    }
  }
}
