#include "Entity.hpp"

#include "Metrics.hpp"
namespace Engine {
Sprite Entity::dummy_sprite;
Sprite Entity::dummy_shadow;
//
//
//
Entity::Entity()
  : sprite(dummy_sprite)
  , shadow(dummy_shadow) {
}
//
//
//
Entity::Entity(Sprite &in_sprite, Sprite &in_shadow)
  : sprite(in_sprite)
  , shadow(in_shadow) {
  perspective_width = sprite.getLocalBounds().width;
}
//
//
//
void Entity::update() {
  sprite.setPosition(movable.getX(), movable.getY());
  sprite.animate();
}
//
//
//
Direction Entity::directionTo(const Entity &in_entity) const {
  Vector3 direction = in_entity.movable.getPosition() - movable.getPosition();
  direction.roundAngle(45);
  direction.normalise();
  Compass c(direction);
  return c.direction;
}
//
//
//
void Entity::perspectivize(const float in_camera_height) const {
  if (perspectivizable) {
    // size depending on distance from camera
    float dimensions = perspective_width;
    float dist_from_camera = in_camera_height - movable.getZ();

    // other side of camera, don't perspectivize!
    if (dist_from_camera <= 0) {
      sprite.setScale(0, 0);
      shadow.setScale(100, 100);
      return;
    }

    float angular_diameter = 2 * (atanf(dimensions / (2 * dist_from_camera)));
    float degs = Degrees(angular_diameter);
    float sprite_scale_factor = degs / dimensions;
    float sprite_ratio = dimensions / sprite.getLocalBounds().width;
    sprite_scale_factor *= sprite_ratio;
    sprite.setScale(sprite_scale_factor, sprite_scale_factor);
    shadow.setScale(sprite_scale_factor, sprite_scale_factor);

    // shadow
    shadow.setPosition(sprite.getPosition());
    shadow.move(shadow_offset, shadow_offset);

    // y offset due to height
    float z_cm = movable.getZ() * Metrics::Z_PERSP_OFFSET;
    if (Math::greater_than(z_cm, 0)) {
      float y_offset = Metrics::Y_OFFSET_DUE_TO_HEIGHT * z_cm;
      sprite.move(0, -y_offset);
    }
  }
}
} // namespace Engine
