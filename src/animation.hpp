#pragma once
#include <array>
#include <cassert>
#include <vector>
#include <map>
#include <SFML/Graphics/Sprite.hpp>

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
  std::array<sf::IntRect, MAX_ANIMATION_FRAMES> frames{};
};
inline std::map<sf::Sprite *, Animation> live_animations;

/**
 * @brief init
 * @param anim
 * @param _frame_time
 * @param _frames
 */
void init(Animation &anim, int _frame_time, std::vector<int> &_frames, std::vector<sf::IntRect> &frame_rects);
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
sf::IntRect frame(Animation &anim);
/**
 * @brief update_animations
 */
void update_animations();
