#include "player.hpp"

#include "debug.hpp"
#include "globals.hpp"
#include "physics.hpp"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
sf::Sprite &get_player_sprite(Player &player) {
  return sprite_pool[entity_pool[player.entity].sprite];
}
// -----------------------------------------------------------------------------
// get_player_shadow_sprite
// -----------------------------------------------------------------------------
sf::Sprite &get_player_shadow_sprite(Player &player) {
  return sprite_pool[get_player_shadow_entity(player).sprite];
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Entity &get_player_entity(Player &player) { return entity_pool[player.entity]; }
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Entity &get_player_shadow_entity(Player &player) {
  return entity_pool[player.shadow_entity];
}
// -----------------------------------------------------------------------------
// make_player_sprite
// -----------------------------------------------------------------------------
void make_player_sprite(int sprite, const std::string &spritesheet) {
  sf::Texture *tex = acquire_texture(spritesheet);
  sprite_pool[sprite].setTexture(*tex);
}

// -----------------------------------------------------------------------------
// init_players
// -----------------------------------------------------------------------------
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
    entity_pool[e].co_friction = 5.f;  // direct control
    entity_pool[e].terminal_velocity = 0.03f;
    entity_pool[e].position.x = 40 * i + PLAYER_SPRITE_WIDTH;
    entity_pool[e].position.y = PLAYER_SPRITE_HEIGHT;
    make_player_sprite(entity_pool[e].sprite, p.spritesheet);
    set_sprite_z(sprite_pool[entity_pool[e].sprite], (rand() % 50) + 5);
    get_player_sprite(p).setOrigin(PLAYER_SPRITE_WIDTH / 2,
                                   PLAYER_SPRITE_HEIGHT);

    init_player_shadow(p);
    players.push_back(p);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void init_player_shadow(Player &player) {
  int e = acquire_entity();
  player.shadow_entity = e;
  get_player_shadow_entity(player).sprite =
      acquire_sprite(&get_player_shadow_entity(player));
  make_player_sprite(get_player_shadow_entity(player).sprite,
                     player.spritesheet);
  set_sprite_z(sprite_pool[get_player_shadow_entity(player).sprite], 1);
}

// -----------------------------------------------------------------------------
// release_players
// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
// think
// -----------------------------------------------------------------------------
void think(Player &player) {}

// -----------------------------------------------------------------------------
// set_animation
// -----------------------------------------------------------------------------
void start_player_animation(Player &player, PlayerAnimation id) {
  Animation anim;
  load_player_animation_frames(anim, id);
  live_animations.insert(std::make_pair(player.entity, anim));
}

// -----------------------------------------------------------------------------
// stop_animation
// -----------------------------------------------------------------------------
void stop_animation(Player &player) { live_animations.erase(player.entity); }
// -----------------------------------------------------------------------------
// update_players
// -----------------------------------------------------------------------------
void update_players(std::vector<Player> &players, Ball &ball) {
  for (auto &player : players) {
    think(player);
    get_player_sprite(player).setPosition(get_player_entity(player).position.x,
                                          get_player_entity(player).position.y);
    get_player_shadow_sprite(player).setPosition(
        get_player_entity(player).position.x + 2,
        get_player_entity(player).position.y + 2);
    if (!perspectivize(get_player_sprite(player),
                       get_player_entity(player).position.z,
                       get_player_sprite(player).getLocalBounds().width, 50)) {
      get_player_sprite(player).setPosition(
          -get_player_sprite(player).getGlobalBounds().left,
          -get_player_sprite(player).getGlobalBounds().top);

      float offset = get_player_entity(player).velocity.z > 0 ? 0.2f : -0.2f;

      get_player_shadow_sprite(player).setScale(
          get_player_shadow_sprite(player).getScale().x + offset,
          get_player_shadow_sprite(player).getScale().y + offset);
    } else {
      get_player_shadow_sprite(player).setScale(
          get_player_sprite(player).getScale().x,
          get_player_sprite(player).getScale().y);
    }

    player.feet.setPosition(
        get_player_entity(player).position.x - player.feet.getRadius(),
        get_player_entity(player).position.y - player.feet.getRadius() * 2);

    debug_shapes.emplace_back(&player.feet);

    // tmp check collision with
    if (collides(player.feet, ball.collidable)) {
      Entity ball_entity = get_ball_entity(ball);
      auto force = get_player_entity(player).velocity.normalise() * 100;
      apply_force(ball_entity, force);
    }
  }
  update_animations();
}
