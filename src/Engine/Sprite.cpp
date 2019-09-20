#include "Sprite.hpp"
#include "Metrics.hpp"
#include "Vector.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <math.h>
#include <cassert>
//
//
//
namespace Engine {
bool Sprite::draw_bounds = false;
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
void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  sf::Sprite::draw(target, states);

  if (draw_bounds) {
    sf::RectangleShape bounds{
        sf::Vector2f{getGlobalBounds().width, getGlobalBounds().height}};
    bounds.setPosition({getGlobalBounds().left, getGlobalBounds().top});
    bounds.setFillColor(sf::Color::Transparent);
    bounds.setOutlineColor(sf::Color::Magenta);
    bounds.setOutlineThickness(1);

    target.draw(bounds);
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
//
//
//
bool Sprite::perspectivize(float in_z, float in_width, float in_camera_height) {
  // size depending on distance from camera
  float dimensions = in_width;
  float dist_from_camera = in_camera_height - z;

  // other side of camera, don't perspectivize!
  if (dist_from_camera <= 0) {
    return false;
  }

  float angular_diameter = 2 * (atanf(dimensions / (2 * dist_from_camera)));
  float degs = DEGREES(angular_diameter);
  float sprite_scale_factor = degs / dimensions;
  float sprite_ratio = dimensions / getLocalBounds().width;
  sprite_scale_factor *= sprite_ratio;
  setScale(sprite_scale_factor, sprite_scale_factor);

  // y offset due to height
  float z_cm = z * Metrics::CM_PER_PIXEL;
  if (Floats::greater_than(z_cm, 0)) {
    float y_offset = Metrics::Y_OFFSET_DUE_TO_HEIGHT * z_cm;
    move(0, -y_offset);
  }

  return true;
}
}  // namespace Engine
