#pragma once
#include "animation.hpp"
#include "data.hpp"
#include "globals.hpp"
#include "player_animations.hpp"
#include "texture.hpp"

#include <gamelib3/compass/compass.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <array>
#include <map>
#include <string>
#include <vector>

inline const int PLAYER_SPRITESHEET_ROWS = 4;
inline const int PLAYER_SPRITESHEET_COLS = 24;
inline const int PLAYER_SPRITE_FRAMES = 72;
inline const int PLAYER_SPRITE_WIDTH = 32;
inline const int PLAYER_SPRITE_HEIGHT = 32;

inline const int PLAYER_SHADOW_SPRITESHEET_ROWS = 4;
inline const int PLAYER_SHADOW_SPRITESHEET_COLS = 24;
inline const int PLAYER_SHADOW_SPRITE_FRAMES = 72;
inline const int PLAYER_SHADOW_SPRITE_WIDTH = 32;
inline const int PLAYER_SHADOW_SPRITE_HEIGHT = 32;

inline const int PLAYER_PERSPECTIVE_WIDTH = 32;

inline std::vector<sf::IntRect> player_frames;
inline std::vector<sf::IntRect> player_shadow_frames;
/**
 * @brief The Player struct
 */
struct Player {
  int entity = -1;
  int shadow_entity = -1;
  std::string spritesheet;
  int shirt_number = 0;
  sf::CircleShape feet{6};
  gamelib3::Compass facing;
};
/**
 * @brief get_entity
 * @param ball
 * @return
 */
Entity &get_player_entity(Player &player);
/**
 * @brief get_player_shadow_entity
 * @param player
 * @return
 */
Entity &get_player_shadow_entity(Player &player);
/**
 * @brief get_sprite
 * @param player
 * @return
 */
sf::Sprite &get_player_sprite(Player &player);
/**
 * @brief get_player_shadow_sprite
 * @param player
 * @return
 */
sf::Sprite &get_player_shadow_sprite(Player &player);
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
 * @brief init_player_shadow
 * @param player
 */
void init_player_shadow(Player &player);
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
void start_player_animation(Player &player, PlayerAnimation id);
/**
 * @brief stop_animation
 * @param player
 */
void stop_animation(Player &player);
/**
 * @brief update_players
 * @param players
 */
void update_players(std::vector<Player> &players, Ball &ball);
