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
      val = width;
      updating = false;
      bar.setFillColor(sf::Color::Red);
      maxed_ticks = 40;
    }else if((val/width)*100 > sweet_spot){
      bar.setFillColor(sf::Color::Yellow);
      maxed_ticks = 15;
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
void ProgressBar::setPosition(float in_x, float in_y) {
  x = in_x;
  y = in_y;
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
void ProgressBar::reset() {
  if (--maxed_ticks == 0) {
    maxed_ticks = 1;
    val = 0;
    updating = false;
    bar.setFillColor(sf::Color::Green);
  }
}
//
//
//
float ProgressBar::getWidth() { return width; }
//
//
//
float ProgressBar::getHeight() { return height; }
//
//
//
void ProgressBar::setSweetSpot(int in_percent){
  sweet_spot = in_percent;
}
}  // namespace Engine
