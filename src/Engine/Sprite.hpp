#pragma once

#include "SpriteAnimation.hpp"

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
  Sprite(std::shared_ptr<sf::Texture> in_texture);
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

  /// a list of shapes for debug drawing
  std::vector<sf::Shape*> debug_shapes;
  /// for perspective
  float entity_height = 0.F;
  Sprite* shadow = nullptr;

 protected:
  /// managed texture
  std::shared_ptr<sf::Texture> texture;
  /// frames
  std::vector<sf::IntRect> frames;
  /// track current frame
  int current_frame = 0;
  /// animation
  SpriteAnimation* animation = nullptr;
  /// animation controller
  bool animating = false;
  /// scale according to distance from camera?
  bool perspectivizable = true;
  /// desired width of sprite unprespectervized
  float perspective_width = 0;
  /**
   * @brief unclutter draw function
   * @param target
   */
  void draw_debug(sf::RenderTarget& target) const;
};
}  // namespace Engine
