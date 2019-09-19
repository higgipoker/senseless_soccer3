#include "Sprite.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

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
Sprite::Sprite(std::shared_ptr<sf::Texture> in_texture) : texture(in_texture){
  setTexture(*texture.get());
}
//
//
//
void Sprite::init(const SpriteSetDefinition &_def) {
  int x = _def.frame_width * _def.start_col;
  int y = _def.frame_height * _def.start_row;
  int col = _def.start_col;
  int frame_count = _def.spriteset_frames;
  while (--frame_count >= 0) {
    sf::IntRect rect;
    rect.left = x;
    rect.top = y;
    rect.width = _def.frame_width;
    rect.height = _def.frame_height;
    frames.push_back(rect);

    // next col
    x += _def.frame_width;

    // next row
    if (++col == _def.sheet_cols) {
      x = 0;
      y += _def.frame_height;
      col = 0;
    }
  }
  setFrame(current_frame);
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
int Sprite::getFrame(){
  return current_frame;
}
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
