#pragma once
#include <array>
#include <cassert>
#include <vector>

static const int MAX_ANIMATION_FRAMES = 50;

/**
 * @brief The Animation struct
 */
struct Animation {
  int frame_time = 0;
  int timer = 0;
  int number_frames = 0;
  int current_frame = 0;
  bool loop = true;
  bool running = true;
  std::array<int, MAX_ANIMATION_FRAMES> frames{};
};
/**
 * @brief init
 * @param anim
 * @param _frame_time
 * @param _frames
 */
void init(Animation &anim, int _frame_time, std::vector<int> &_frames);
/**
 * @brief next_frame
 * @param anim
 */
void next_frame(Animation &anim);
/**
 * @brief step
 * @param anim
 */
void step(Animation &anim);
/**
 * @brief frame
 * @param anim
 * @return
 */
int frame(Animation &anim);
