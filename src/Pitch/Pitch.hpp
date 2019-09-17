#pragma once

#include "Engine/Sprite.hpp"

class Pitch : public Engine::Sprite {
 public:
  /**
   * @brief Pitch
   * @param in_filename
   * @param in_target
   */
  Pitch(const std::string& in_filename);
  /**
   * @brief create
   */
  void create();
  /**
   * @brief setRect
   * @param in_rect
   */
  void setRect(const sf::IntRect in_rect);

  protected:
  /// pitch is a special typ of repeating sprite so needs camera rect
  sf::IntRect camera_rect;

};
