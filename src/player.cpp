#include "player.hpp"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
sf::Sprite &get_sprite(Player &player) {
  return sprite_pool[entity_pool[player.entity].sprite];
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Entity &get_player_entity(Player &player) { return entity_pool[player.entity]; }

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
    p.spritesheet = Globals::GFX_FOLDER + "player/player.png";

    int s = acquire_sprite(&entity_pool[e]);
    if (s == -1) {
      std::cout << "no sprite" << std::endl;
      release_entity(e);
      continue;
    }

    entity_pool[e].sprite = s;
    entity_pool[e].co_friction = 1.0f;
    entity_pool[e].terminal_velocity = 0.03f;
    make_player_sprite(entity_pool[e].sprite, p.spritesheet);
    set_sprite_z(sprite_pool[entity_pool[e].sprite],(rand()%50)+5);
    players.push_back(p);
  }
}

// -----------------------------------------------------------------------------
// release_players
// -----------------------------------------------------------------------------
void release_players(std::vector<Player> &players) {
  for (auto &player : players) {
    release_entity(player.entity);
    release_sprite(entity_pool[player.entity].sprite);
    release_texture(player.spritesheet);
  }
}

// -----------------------------------------------------------------------------
// think
// -----------------------------------------------------------------------------
void think(Player &player) {
  // std::cout << "player " << player.shirt_number << " thinking..." <<
  // std::endl;
}

// -----------------------------------------------------------------------------
// set_animation
// -----------------------------------------------------------------------------
void start_animation(Player &player, AnimationID id) {
  Animation anim;
  load_animation_frames(anim, id);
  live_animations.insert(std::make_pair(&player, anim));
}

// -----------------------------------------------------------------------------
// stop_animation
// -----------------------------------------------------------------------------
void stop_animation(Player &player) { live_animations.erase(&player); }

// -----------------------------------------------------------------------------
// update_animations
// -----------------------------------------------------------------------------
void update_animations() {
  for (auto &anim : live_animations) {
    step(anim.second);
    get_sprite(*anim.first).setTextureRect(player_frames[frame(anim.second)]);
  }
}
