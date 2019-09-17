#pragma once

#include "SpriteAnimation.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <string>
#include <vector>

namespace Engine {
/**
 * @brief The SpriteSheetDefinition struct
 */
struct SpriteSetDefinition {
  std::string spritesheet;
  int frame_width = 0;
  int frame_height = 0;
  int spriteset_frames = 0;
  int start_row = 0;
  int start_col = 0;
  int sheet_cols = 0;
};

/**
 * @brief The Sprite class
 */
class Sprite : public sf::Sprite {
 public:
  /**
   * @brief Sprite
   * @param in_target
   */
  Sprite();
  /**
   * @brief Sprite
   */
  Sprite(const std::string & in_filename);

  /**
   * @brief init
   * @param _spritesheet
   * @param _rows
   * @param _cols
   * @param _frames
   * @param _start_row
   * @param _start_col
   */
  void init(const SpriteSetDefinition &_def);
  /**
   * @brief setFrame
   * @param in_frame
   */
  void setFrame(const int in_frame);

  /**
   * @brief setAnimation
   * @param in_animation
   */
  virtual void setAnimation(SpriteAnimation* in_animation);
  /**
   * @brief animate
   */
  void animate();

 protected:
  /// frames
  std::vector<sf::IntRect> frames;
  /// track current frame
  int current_frame = 0;
  /// animation
  SpriteAnimation *animation = nullptr;
};
}  // namespace Engine
