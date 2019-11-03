#pragma once
#include "Types.hpp"
#include "Widget.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
//
//
//
namespace Engine {
//
//
//
enum class Orientation { Vertical, Horizontal };
//
//
//
class ProgressBar : public Widget {
 public:
  //
  //
  //
  ProgressBar(float in_width, float in_height, float in_frames);
  //
  //
  //
  void update() override;
  //
  //
  //
  void start();
  //
  //
  //
  void stop();
  //
  //
  //
  void reset();
  //
  //
  //
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  //
  //
  //
  void setPosition(const float in_x, const float in_y);
  //
  //
  //
  void setCenter(const float in_x, const float in_y);
  //
  //
  //
  float getWidth();
  //
  //
  //
  float getHeight();

 private:
  float x = 20;
  float y = 20;
  float width = 100;
  float height = 10;
  float val = 0;
  float frames = 0;
  float resolution = 0;
  bool updating = true;
  // Orientation orientation = Orientation::Horizontal;
  sf::RectangleShape bar{{width, height}};
  sf::RectangleShape outline{{width, height}};
};

}  // namespace Engine
