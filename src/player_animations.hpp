#pragma once

#include "animation.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <map>
#include <vector>

using Anims = std::vector<int>;
inline std::map<Direction, Animation> player_stand_animations;
inline std::map<Direction, Animation> player_run_animations;

// anim speed for all player anims
static const int player_frame_time = 10;

enum class PlayerAnimationType{
  Stand, Run
};

//
// standing animations
//
inline Anims stand_east{1};
inline Anims stand_southeast{4};
inline Anims stand_south{7};
inline Anims stand_southwest{10};
inline Anims stand_west{13};
inline Anims stand_northwest{16};
inline Anims stand_north{19};
inline Anims stand_northeast{22};
//
// running animations
//
inline Anims run_east{0, 1};
inline Anims run_southeast{3, 5};
inline Anims run_south{6, 8};
inline Anims run_southwest{9, 11};
inline Anims run_west{12, 13};
inline Anims run_northwest{15, 17};
inline Anims run_north{18, 20};
inline Anims run_northeast{21, 23};
//
// sliding animations
//
inline Anims slide_east{24, 25, 26, 26};
inline Anims slide_southeast{27, 28, 29, 29};
inline Anims slide_south{30, 31, 32, 32};
inline Anims slide_southwest{33, 34, 35, 35};
inline Anims slide_west{36, 37, 38, 38};
inline Anims slide_northwest{39, 40, 41, 41};
inline Anims slide_north{42, 43, 44, 44};
inline Anims slide_northeast{45, 46, 47, 47};
/**
 * @brief init_player_animations
 */
void init_player_animations();
