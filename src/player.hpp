#pragma once
#include "animation.hpp"
#include "data.hpp"
#include "globals.hpp"
#include "player_animations.hpp"
#include "texture.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <array>
#include <map>
#include <string>
#include <vector>

namespace Player {
inline const int PLAYER_SPRITESHEET_ROWS = 3;
inline const int PLAYER_SPRITESHEET_COLS = 24;
inline const int PLAYER_SPRITE_FRAMES =
    PLAYER_SPRITESHEET_ROWS * PLAYER_SPRITESHEET_COLS;
inline const int PLAYER_SPRITE_WIDTH = 32;
inline const int PLAYER_SPRITE_HEIGHT = 32;

inline std::array<sf::IntRect, PLAYER_SPRITE_FRAMES> player_frames;

/**
 * @brief The Player struct
 */
struct Player {
  int entity = 0;
  std::string spritesheet;
  int shirt_number = 0;
};

inline std::map<Player *, Animation::Animation> live_animations;

/**
 * @brief get_sprite
 * @param player
 * @return
 */
sf::Sprite &get_sprite(Player &player);

/**
 * @brief get_entity
 * @param player
 * @return
 */
Data::Entity &get_entity(Player &player);

/**
 * @brief populate_player_sprite_frames
 * @param frames
 */
void populate_player_sprite_frames(
    std::array<sf::IntRect, PLAYER_SPRITE_FRAMES> &frames);

/**
 * @brief make_player_sprite
 * @param sprite
 * @param spritesheet
 */
void make_player_sprite(int sprite, const std::string &spritesheet);

/**
 * @brief init_players
 * @param players
 */
void init_players(std::vector<Player> &players);

/**
 * @brief release_players
 * @param players
 */
void release_players(std::vector<Player> &players);

/**
 * @brief think
 * @param player
 */
void think(Player &player);

/**
 * @brief start_animation
 * @param player
 * @param id
 */
void start_animation(Player &player, PlayerAnimations::AnimationID id);

/**
 * @brief stop_animation
 * @param player
 */
void stop_animation(Player &player);

/**
 * @brief update_animations
 */
void update_animations();
}  // namespace Player
