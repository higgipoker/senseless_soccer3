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
  void setPosition(float in_x, float in_y);
  //
  //
  //
  float getWidth();
  //
  //
  //
  float getHeight();
  //
  //
  //
  void setSweetSpot(int in_percent);

 private:
  float x = 20;
  float y = 20;
  float width = 100;
  float height = 10;
  float val = 0;
  float frames = 0;
  float resolution = 0;
  bool updating = true;
  float maxed_ticks = 1;
  int sweet_spot = 90;
  // Orientation orientation = Orientation::Horizontal;
  sf::RectangleShape bar{{width, height}};
  sf::RectangleShape outline{{width, height}};
};

}  // namespace Engine
