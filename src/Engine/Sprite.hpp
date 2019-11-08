#pragma once

#include "SpriteAnimation.hpp"

#include "Types.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Engine {
//
//
//
struct SpriteSetDefinition {
  int vertical_offset = 0;
  int frame_width = 0;
  int frame_height = 0;
  int spriteset_frames = 0;
  int start_row = 0;
  int start_col = 0;
  int sheet_cols = 0;
};
//
//
//
class Sprite : public sf::Sprite {
 public:
  //
  //
  //
  Sprite();
  //
  //
  //
  Sprite(const sf::Texture& texture) : sf::Sprite(texture) {}
  //
  //
  //
  Sprite(SharedPtr<sf::Texture> in_texture);
  //
  //
  //
  void init(const SpriteSetDefinition& in_def);
  //
  //
  //
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  //
  //
  //
  void setFrame(const int in_frame);
  //
  //
  //
  int getFrame();
  //
  //
  //
  virtual void setAnimation(SpriteAnimation* in_animation,
                            bool in_autostart = true);
  //
  //
  //
  void animate();
  //
  //
  //
  void startAnimating();
  //
  //
  //
  void stopAnimating();
  //
  //
  //
  void setBasePerspectiveWidth(const float in_width);
  //
  //
  //
  virtual void perspectivize(const float in_camera_height);
  //
  //
  //
  inline void setPerspectivizable(bool in_status) {
    perspectivizable = in_status;
  }
  /// a list of shapes for debug drawing
  std::vector<sf::Shape*> debug_shapes;
  /// for perspective
  float entity_height = 0.F;
  Sprite* shadow = nullptr;

 protected:
  /// frames
  std::vector<sf::IntRect> frames;
  /// track current frame
  int current_frame = 0;
  /// animation
  SpriteAnimation* animation = nullptr;
  /// animation controller
  bool animating = false;
  /// scale according to distance from camera?
  bool perspectivizable = false;
  /// desired width of sprite unprespectervized
  float perspective_width = 0;
  /**
   * @brief unclutter draw function
   * @param target
   */
  void draw_debug(sf::RenderTarget& target) const;
};
}  // namespace Engine
