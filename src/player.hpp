#pragma once
#include "entity.hpp"
#include "globals.hpp"
#include "texture.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <array>
#include <vector>

namespace Player {
static const int PLAYER_SPRITESHEET_ROWS = 3;
static const int PLAYER_SPRITESHEET_COLS = 24;
static const int PLAYER_SPRITE_FRAMES =
    PLAYER_SPRITESHEET_ROWS * PLAYER_SPRITESHEET_COLS;
static const int PLAYER_SPRITE_WIDTH = 32;
static const int PLAYER_SPRITE_HEIGHT = 32;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static void populate_player_sprite_frames(
    std::array<sf::IntRect, PLAYER_SPRITE_FRAMES> &frames) {
  int x = 0;
  int y = 0;
  int row = 0;
  int col = 0;
  for (auto &rect : frames) {
    rect.left = x;
    rect.top = y;
    rect.width = PLAYER_SPRITE_WIDTH;
    rect.height = PLAYER_SPRITE_HEIGHT;

    x += PLAYER_SPRITE_WIDTH;

    if (++col == PLAYER_SPRITESHEET_COLS) {
      x = 0;
      y += PLAYER_SPRITE_HEIGHT;
      col = 0;
    }
  }
}

static std::array<sf::IntRect, PLAYER_SPRITE_FRAMES> player_frames;
/**
 * @brief The Player struct
 */
struct Player {
  Entity::Entity *entity = nullptr;
  Entity::SortableSprite *sprite = nullptr;
  std::string spritesheet;
  int current_frame = 0;
  int shirt_number = 0;
};

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static void make_player_sprite(Entity::SortableSprite *sprite,
                               const std::string &spritesheet) {
  sf::Texture *tex = Texture::acquire_texture(spritesheet);
  sprite->sprite.setTexture(*tex);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static void init_players(std::vector<Player> &players) {
  for (int i = 0; i < 11; ++i) {
    Entity::Entity *e = Entity::acquire_entity();
    e->type = Entity::EntityType::Player;

    Player p;
    p.shirt_number = i + 1;
    p.entity = e;
    p.spritesheet = Globals::GFX_FOLDER + "player/player.png";
    p.sprite = Entity::acquire_sprite();
    make_player_sprite(p.sprite, p.spritesheet);
    players.push_back(p);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static void release_players(std::vector<Player> &players) {
  for (auto &player : players) {
    Entity::release_entity(player.entity->id);
    Entity::release_sprite(player.sprite);
    Texture::release_texture(player.spritesheet);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
static void think(Player &player) {
  std::cout << "player " << player.shirt_number << " thinking..." << std::endl;
}
}  // namespace Player
