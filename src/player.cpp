#include "player.hpp"
#include "debug.hpp"
#include "globals.hpp"
#include "physics.hpp"
//
//
//
sf::Sprite &get_player_sprite(Player &player) {
  return sprite_pool[entity_pool[player.entity].sprite];
}
//
//
//
sf::Sprite &get_player_shadow_sprite(Player &player) {
  return sprite_pool[get_player_shadow_entity(player).sprite];
}
//
//
//
Entity &get_player_entity(Player &player) { return entity_pool[player.entity]; }
//
//
//
Entity &get_player_shadow_entity(Player &player) {
  return entity_pool[player.shadow_entity];
}
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
void init_players(std::vector<Player> &players) {
  for (int i = 0; i < 11; ++i) {
    int e = acquire_entity();

    if (e == -1) {
      std::cout << "no entity" << std::endl;
      continue;
    }

    entity_pool[e].type = EntityType::Player;
    Player p;
    p.shirt_number = i + 1;
    p.entity = e;
    p.spritesheet = Globals::GFX_FOLDER + "playerandball.png";

    int s = acquire_sprite(&entity_pool[e]);
    if (s == -1) {
      std::cout << "no sprite" << std::endl;
      release_entity(e);
      continue;
    }

    entity_pool[e].sprite = s;
    entity_pool[e].co_friction = 25.f;  // direct control
    entity_pool[e].co_air_resistance = 0;
    entity_pool[e].terminal_velocity = 0.03f;
    entity_pool[e].position.x = 40 * i + PLAYER_SPRITE_WIDTH;
    entity_pool[e].position.y = PLAYER_SPRITE_HEIGHT;
    entity_pool[e].speed = 100;
    make_player_sprite(entity_pool[e].sprite, p.spritesheet);
    set_sprite_z(sprite_pool[entity_pool[e].sprite], (rand() % 50) + 5);
    get_player_sprite(p).setOrigin(PLAYER_SPRITE_WIDTH / 2,
                                   PLAYER_SPRITE_HEIGHT);

    init_player_shadow(p);

    p.facing.direction = Direction::SOUTH;
    players.push_back(p);
  }
}
//
//
//
void init_player_shadow(Player &player) {
  int e = acquire_entity();
  player.shadow_entity = e;
  get_player_shadow_entity(player).sprite =
      acquire_sprite(&get_player_shadow_entity(player));
  make_player_sprite(get_player_shadow_entity(player).sprite,
                     player.spritesheet);
  set_sprite_z(sprite_pool[get_player_shadow_entity(player).sprite], 1);
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
void start_player_animation(Player &player, PlayerAnimation id) {
  Animation anim;
  load_player_animation_frames(anim, id);
  live_animations[player.entity] = anim;
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
  to_ball.direction =
      direction_to(get_player_entity(player), get_ball_entity(ball));
  player.facing = to_ball.direction;

  switch (to_ball.direction) {
    case Direction::NORTH:
      start_player_animation(player, PlayerAnimation::StandNorth);
      break;
    case Direction::NORTH_EAST:
      start_player_animation(player, PlayerAnimation::StandNorthEast);
      break;
    case Direction::EAST:
      start_player_animation(player, PlayerAnimation::StandEast);
      break;
    case Direction::SOUTH_EAST:
      start_player_animation(player, PlayerAnimation::StandSouthEast);
      break;
    case Direction::SOUTH:
      start_player_animation(player, PlayerAnimation::StandSouth);
      break;
    case Direction::SOUTH_WEST:
      start_player_animation(player, PlayerAnimation::StandSouthWest);
      break;
    case Direction::WEST:
      start_player_animation(player, PlayerAnimation::StandWest);
      break;
    case Direction::NORTH_WEST:
      start_player_animation(player, PlayerAnimation::StandNorthWest);
      break;
    case Direction::NONE:
      // start_player_animation(player, PlayerAnimation::RunNorthEast);
      break;
  }
  if (Floats::greater_than(get_player_entity(player).velocity.magnitude2d(),
                           0)) {
    change_player_state(player, PlayerState::Run);
  }
}
//
//
//
void do_run_state(Player &player, Ball &ball) {
  // update direction
  player.facing.fromVector(get_player_entity(player).velocity.normalise());
  if (player.old_direction != player.facing) {
    switch (player.facing.direction) {
      case Direction::NORTH:
        start_player_animation(player, PlayerAnimation::RunNorth);
        break;
      case Direction::NORTH_EAST:
        start_player_animation(player, PlayerAnimation::RunNorthEast);
        break;
      case Direction::EAST:
        start_player_animation(player, PlayerAnimation::RunEast);
        break;
      case Direction::SOUTH_EAST:
        start_player_animation(player, PlayerAnimation::RunSouthEast);
        break;
      case Direction::SOUTH:
        start_player_animation(player, PlayerAnimation::RunSouth);
        break;
      case Direction::SOUTH_WEST:
        start_player_animation(player, PlayerAnimation::RunSouthWest);
        break;
      case Direction::WEST:
        start_player_animation(player, PlayerAnimation::RunWest);
        break;
      case Direction::NORTH_WEST:
        start_player_animation(player, PlayerAnimation::RunNorthWest);
        break;
      case Direction::NONE:
        // start_player_animation(player, PlayerAnimation::RunNorthEast);
        break;
    }
  }
  if (Floats::equal(get_player_entity(player).velocity.magnitude2d(), 0)) {
    change_player_state(player, PlayerState::Stand);
  }
}
//
//
//
void update_player(Player &player, Ball &ball) {
  // player's can't exert a force whilst in the air!
  if (Floats::greater_than(get_player_entity(player).position.z, 0)) {
    get_player_entity(player).force.reset();
  }

  // update player sprite and shadow
  get_player_sprite(player).setPosition(get_player_entity(player).position.x,
                                        get_player_entity(player).position.y);
  get_player_shadow_sprite(player).setPosition(
      get_player_entity(player).position.x + 2,
      get_player_entity(player).position.y + 2);

  // if perspectivize reutrns false then the sprite is behind the camera
  if (perspectivize(get_player_sprite(player),
                    get_player_entity(player).position.z,
                    get_player_sprite(player).getLocalBounds().width, 50)) {
    get_player_shadow_sprite(player).setScale(
        get_player_sprite(player).getScale().x,
        get_player_sprite(player).getScale().y);
  } else {
    get_player_sprite(player).setPosition(
        -get_player_sprite(player).getGlobalBounds().left,
        -get_player_sprite(player).getGlobalBounds().top);

    get_player_shadow_sprite(player).setScale(
        get_player_shadow_sprite(player).getScale().x,
        get_player_shadow_sprite(player).getScale().y);
  }

  // updat feet (collidable shape for kicking)
  player.feet.setPosition(
      get_player_entity(player).position.x - player.feet.getRadius(),
      get_player_entity(player).position.y - player.feet.getRadius());
  player.control.setPosition(
      get_player_entity(player).position.x - player.control.getRadius(),
      get_player_entity(player).position.y - player.control.getRadius());

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

      get_ball_entity(ball).velocity.reset();

      // set new position
      get_ball_entity(ball).position = ball_pos;
    }
  }
  player.old_direction = player.facing;

  // check for ball collision
  if (collides(player.feet, ball.collidable)) {
    Vector3 force = player.facing.toVector();
    force *= 7000;
    get_ball_entity(ball).velocity.reset();
    apply_force(get_ball_entity(ball), force);
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
