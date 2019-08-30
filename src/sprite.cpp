#include "sprite.hpp"
#include <gamelib3/math/vector.hpp>
#include <gamelib3/physics/metrics.hpp>

using namespace gamelib3;
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void set_sprite_z(SortableSprite& sprite, float z) {
  if (sprite.z != z) {
    sprite.z = z;
    *SortableSprite::sort_flag = false;
  }
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void perspectivize(sf::Sprite& sprite, float z, float width,
                   float camera_height) {
  // size depending on distance from camera
  float dimensions = width;
  float dist_from_camera = camera_height - z;
  float angular_diameter = 2 * (atanf(dimensions / (2 * dist_from_camera)));
  float degs = DEGREES(angular_diameter);
  float sprite_scale_factor = degs / dimensions;
  float sprite_ratio = dimensions / sprite.getLocalBounds().width;
  sprite_scale_factor *= sprite_ratio;
  sprite.setScale(sprite_scale_factor, sprite_scale_factor);
  // y offset due to height
  float z_cm = z * CM_PER_PIXEL;

  if (Floats::greater_than(z_cm, 0)) {
    float y_offset = Y_OFFSET_DUE_TO_HEIGHT * z_cm;
    sprite.move(0, -y_offset);
  }
}
