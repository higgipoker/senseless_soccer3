#pragma once
#include "animation.hpp"

#include <vector>

using Anims = std::vector<int>;
const int ball_frame_time = 3;
/**

 * @brief The BallAnimation enum
 */
enum class BallAnimation { RollLeft };
/**
 * @brief roll_left
 * @return
 */
Anims roll_left();
/**
 * @brief load_animation_frames
 * @param anim
 * @param id
 */
void load_ball_animation_frames(Animation &anim, BallAnimation id);
