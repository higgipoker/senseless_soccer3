#pragma once
#include "Types.hpp"
#include "Widget.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
namespace Engine {
enum class Orientation { Vertical, Horizontal };

//
//
//
class ProgressBar : public Widget {
 public:
  //
  //
  //
  ProgressBar();
  //
  //
  //
  void update() override;
  //
  //
  //
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  //
  //
  //
  void setPosition(float in_x, float in_y);

 private:
  float x = 20;
  float y = 20;
  float width = 100;
  float height = 10;
  Orientation orientation = Orientation::Horizontal;
  float resolution = 0;
  float val = 0;
  float ticks = 0;
  sf::RectangleShape bar{{width, height}};
  sf::RectangleShape outline{{width, height}};
};

}  // namespace Engine
