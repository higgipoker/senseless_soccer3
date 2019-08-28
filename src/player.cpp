#include "player.hpp"

namespace Player {

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
sf::Sprite &get_sprite(Player &player) {
  return Data::sprite_pool[Data::entity_pool[player.entity].sprite];
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Data::Entity &get_entity(Player &player) {
  return Data::entity_pool[player.entity];
}

// -----------------------------------------------------------------------------
// populate_player_sprite_frames
// -----------------------------------------------------------------------------
void populate_player_sprite_frames(
    std::array<sf::IntRect, PLAYER_SPRITE_FRAMES> &frames) {
  int x = 0;
  int y = 0;
  for (auto &rect : frames) {
    rect.left = x;
    rect.top = y;
    rect.width = PLAYER_SPRITE_WIDTH;
    rect.height = PLAYER_SPRITE_HEIGHT;
    int col = 0;
    x += PLAYER_SPRITE_WIDTH;

    if (++col == PLAYER_SPRITESHEET_COLS) {
      x = 0;
      y += PLAYER_SPRITE_HEIGHT;
    }
  }
}

// -----------------------------------------------------------------------------
// make_player_sprite
// -----------------------------------------------------------------------------
void make_player_sprite(int sprite, const std::string &spritesheet) {
  sf::Texture *tex = Texture::acquire_texture(spritesheet);
  Data::sprite_pool[sprite].setTexture(*tex);
}

// -----------------------------------------------------------------------------
// init_players
// -----------------------------------------------------------------------------
void init_players(std::vector<Player> &players) {
  for (int i = 0; i < 11; ++i) {
    int e = Data::acquire_entity();

    if (e == -1) {
      std::cout << "no entity" << std::endl;
      continue;
    }

    Data::entity_pool[e].type = Data::EntityType::Player;
    Player p;
    p.shirt_number = i + 1;
    p.entity = e;
    p.spritesheet = Globals::GFX_FOLDER + "player/player.png";

    int s = Data::acquire_sprite(&Data::entity_pool[e]);
    if (s == -1) {
      std::cout << "no sprite" << std::endl;
      Data::release_entity(e);
      continue;
    }

    Data::entity_pool[e].sprite = s;
    make_player_sprite(Data::entity_pool[e].sprite, p.spritesheet);
    Data::sprite_pool[Data::entity_pool[e].sprite].set_z(i + 1);
    players.push_back(p);
  }
}

// -----------------------------------------------------------------------------
// release_players
// -----------------------------------------------------------------------------
void release_players(std::vector<Player> &players) {
  for (auto &player : players) {
    Data::release_entity(player.entity);
    Data::release_sprite(Data::entity_pool[player.entity].sprite);
    Texture::release_texture(player.spritesheet);
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
void start_animation(Player &player, PlayerAnimations::AnimationID id) {
  Animation::Animation anim;
  PlayerAnimations::load_animation_frames(anim, id);
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
}  // namespace Player
