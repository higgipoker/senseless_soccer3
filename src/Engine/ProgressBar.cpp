#include "ProgressBar.hpp"
//
//
//
namespace Engine {
//
//
//
ProgressBar::ProgressBar(float in_width, float in_height, float in_frames)
    : width(in_width), height(in_height), frames(in_frames) {
  bar.setFillColor(sf::Color::Green);
  outline.setFillColor({0, 0, 0, 0});
  outline.setOutlineColor(sf::Color::Red);
  outline.setOutlineThickness(1);
  outline.setSize({width, height});
  resolution = width / frames;
  updating = false;
}
//
//
//
void ProgressBar::update() {
  bar.setPosition(x, y);
  outline.setPosition(x, y);

  if (updating) {
    val += resolution;
    if (val >= width) {
      val = 0;
    }
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
void ProgressBar::setPosition(const float in_x, const float in_y) {
  x = in_x;
  y = in_y;
}
//
//
//
void ProgressBar::setCenter(const float in_x, const float in_y){
  setPosition(in_x - this->width/2, in_y-this->height/2);
}
//
//
//
void ProgressBar::start() { updating = true; }
//
//
//
void ProgressBar::stop() { updating = false; }
//
//
//
void ProgressBar::reset(){
  val = 0;
}
//
//
//
float ProgressBar::getWidth() { return width; }
//
//
//
float ProgressBar::getHeight() { return height; }
}  // namespace Engine
