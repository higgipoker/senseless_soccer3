#include "ProgressBar.hpp"

namespace Engine {
//
//
//
ProgressBar::ProgressBar() {
  bar.setFillColor(sf::Color::Green);
  outline.setFillColor({0, 0, 0, 0});
  outline.setOutlineColor(sf::Color::Red);
  outline.setOutlineThickness(2);
  outline.setSize({width, height});
}
//
//
//
void ProgressBar::update() {
  bar.setPosition(x, y);
  outline.setPosition(x, y);
  if (++ ++val > width) {
    val = 0;
  }
  bar.setSize({val, height});
}
//
//
//
void ProgressBar::draw(sf::RenderTarget& target,
                       sf::RenderStates states) const {
  target.draw(bar);
  target.draw(outline);
}
//
//
//
void ProgressBar::setPosition(float in_x, float in_y){
  x = in_x;
  y = in_y;
}
}  // namespace Engine
