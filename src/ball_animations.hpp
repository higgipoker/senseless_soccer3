#pragma once
#include "animation.hpp"

#include <vector>

using Anims = std::vector<int>;
const int ball_frame_time = 3;
static inline Anims roll_left { 0, 1, 2, 3, 4, 5, 6};
inline std::map<Direction, Animation> ball_roll_animations;
/**

 * @brief The BallAnimation enum
 */
enum class BallAnimation { RollLeft };

/**
 * @brief init_player_animations
 */
void init_ball_animations();
