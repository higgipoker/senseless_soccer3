#include "Sprite.hpp"
#include "Metrics.hpp"
#include "Vector.hpp"
#include "Debug.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <math.h>
#include <cassert>
//
//
//
namespace Engine {
//
//
//
Sprite::Sprite() {}
//
//
//
Sprite::Sprite(std::shared_ptr<sf::Texture> in_texture) : texture(in_texture) {
  setTexture(*texture.get());
}
//
//
//
void Sprite::init(const SpriteSetDefinition &in_def) {
  int x = in_def.frame_width * in_def.start_col;
  int y = in_def.frame_height * in_def.start_row;
  int col = in_def.start_col;
  int frame_count = in_def.spriteset_frames;
  while (--frame_count >= 0) {
    sf::IntRect rect;
    rect.left = x;
    rect.top = y;
    rect.width = in_def.frame_width;
    rect.height = in_def.frame_height;
    frames.push_back(rect);

    // next col
    x += in_def.frame_width;

    // next row
    if (++col == in_def.sheet_cols) {
      x = 0;
      y += in_def.frame_height;
      col = 0;
    }
  }
  setFrame(current_frame);

  // default set origin to center
  setOrigin(in_def.frame_width / 2, in_def.frame_height / 2);
}
//
//
//
void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  sf::Sprite::draw(target, states);

  if (Debug::flag_draw_bounds) {
    sf::RectangleShape bounds{
        sf::Vector2f{getGlobalBounds().width, getGlobalBounds().height}};
    bounds.setPosition({getGlobalBounds().left, getGlobalBounds().top});
    bounds.setFillColor(sf::Color::Transparent);
    bounds.setOutlineColor(Debug::bounds_color);
    bounds.setOutlineThickness(1);

    target.draw(bounds);
  }
  if(Debug::flag_draw_diagnostics){
    for(auto &shape: debug_shapes){
      target.draw(*shape);
    }
  }
}
//
//
//
void Sprite::setFrame(const int in_frame) {
  current_frame = in_frame;
  setTextureRect(frames.at(current_frame));
}
//
//
//
int Sprite::getFrame() { return current_frame; }
//
//
//
void Sprite::setAnimation(SpriteAnimation *in_animation) {
  animation = in_animation;
  setTextureRect(frames.at(animation->currentFrame()));
}
//
//
//
void Sprite::animate() {
  if (animation) {
    animation->step();
    current_frame = animation->currentFrame();
    setTextureRect(frames.at(current_frame));
  }
}
}  // namespace Engine
