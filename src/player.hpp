#pragma once
#include "animation.hpp"
#include "compass.hpp"
#include "data.hpp"
#include "globals.hpp"
#include "player_animations.hpp"
#include "texture.hpp"

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
inline const int PLAYER_ANIMS = 24;

inline std::vector<sf::IntRect> player_frames;
inline std::vector<sf::IntRect> player_shadow_frames;

// shorthand getters
#define PlayerEntity entity_pool[player.entity]
#define PlayerSprite sprite_pool[entity_pool[player.entity].sprite]
#define PlayerShadowEntity entity_pool[player.shadow_entity]
#define PlayerShadowSprite sprite_pool[PlayerShadowEntity.sprite]

/**
 * @brief The PlayerState enum
 */
enum class PlayerState { Stand, Run };

/**
 * @brief The Player struct
 */
struct Player {
  int entity = -1;
  int shadow_entity = -1;
  int shirt_number = 0;
  sf::CircleShape feet{3.5f};
  sf::CircleShape control{25.0f};
  Compass facing;
  Compass old_direction;
  bool changed_direction = true;
  PlayerState state = PlayerState::Stand;
  bool ball_under_control = false;
};
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
void init_player(Player &player);
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
 * @brief start_player_animation
 * @param player
 * @param id
 */
void start_player_animation(Player &player, PlayerAnimationType type,
                            Direction dir);
/**
 * @brief stop_animation
 * @param player
 */
void stop_animation(Player &player);
/**
 * @brief update_player
 * @param player
 */
void update_player(Player &player);
/**
 * @brief update_players
 * @param players
 */
void update_players(std::vector<Player> &players, Ball &ball);
/**
 * @brief do_stand_state
 * @param player
 */
void do_stand_state(Player &player, Ball &ball);
/**
 * @brief do_run_state
 * @param player
 */
void do_run_state(Player &player, Ball &ball);
/**
 * @brief change_player_state
 * @param player
 */
void change_player_state(Player &player, PlayerState new_state);
/**
 * @brief do_close_control
 * @param player
 * @param ball
 */
void do_close_control(Player &player, Ball &ball);
/**
 * @brief do_dribble
 * @param player
 * @param ball
 */
void do_dribble(Player &player, Ball &ball);
