#pragma once

#include "SpriteAnimation.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <memory>
#include <string>
#include <vector>

namespace Engine {
/**
 * @brief The SpriteSheetDefinition struct
 */
struct SpriteSetDefinition {
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
  Sprite(std::shared_ptr<sf::Texture> in_texture);

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
   * @brief drawBounds
   */
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  /**
   * @brief setFrame
   * @param in_frame
   */
  void setFrame(const int in_frame);
  /**
   * @brief getFrame
   * @return
   */
  int getFrame();
  /**
   * @brief setAnimation
   * @param in_animation
   */
  virtual void setAnimation(SpriteAnimation* in_animation);
  /**
   * @brief animate
   */
  void animate();
  /**
   * @brief perspectivize
   * @param z
   * @param width
   * @param camera_height
   * @return
   */
  bool perspectivize(float in_z, float in_width, float in_camera_height);

  ///debug
  static bool draw_bounds;

 protected:
  /// managed texture
  std::shared_ptr<sf::Texture> texture;
  /// frames
  std::vector<sf::IntRect> frames;
  /// track current frame
  int current_frame = 0;
  /// animation
  SpriteAnimation *animation = nullptr;
};
}  // namespace Engine
