#include "Entity.hpp"

#include "Metrics.hpp"
namespace Engine {
//
//
//
Entity::Entity(Sprite &in_sprite, Sprite &in_shadow)
    : movable(default_movable), sprite(in_sprite), shadow(in_shadow) {
  perspective_width = sprite.getLocalBounds().width;
}
//
//
//
Entity::Entity(Movable &in_movable, Sprite &in_sprite, Sprite &in_shadow)
    : movable(in_movable), sprite(in_sprite), shadow(in_shadow) {
  perspective_width = sprite.getLocalBounds().width;
}
//
//
//
void Entity::Update(){
  sprite.setPosition(movable.position.x, movable.position.y);
  sprite.animate();
}
//
//
//
Engine::Direction Entity::directionTo(const Entity &in_entity) {
  Vector3 direction = in_entity.movable.position - movable.position;
  Compass c(direction.roundAngle(45).normalise());
  return c.direction;
}
//
//
void Entity::perspectivize(const float in_camera_height) {
  // size depending on distance from camera
  float dimensions = perspective_width;
  float dist_from_camera = in_camera_height - movable.position.z;

  // other side of camera, don't perspectivize!
  if (dist_from_camera <= 0) {
    sprite.setScale(0, 0);
    shadow.setScale(100, 100);
    return;
  }

  float angular_diameter = 2 * (atanf(dimensions / (2 * dist_from_camera)));
  float degs = DEGREES(angular_diameter);
  float sprite_scale_factor = degs / dimensions;
  float sprite_ratio = dimensions / sprite.getLocalBounds().width;
  sprite_scale_factor *= sprite_ratio;
  sprite.setScale(sprite_scale_factor, sprite_scale_factor);
  shadow.setScale(sprite_scale_factor, sprite_scale_factor);

  // shadow
  shadow.setPosition(sprite.getPosition());
  shadow.move(shadow_offset, shadow_offset);

  // y offset due to height
  float z_cm = movable.position.z * Metrics::CM_PER_PIXEL;
  if (Floats::greater_than(z_cm, 0)) {
    float y_offset = Metrics::Y_OFFSET_DUE_TO_HEIGHT * z_cm;
    sprite.move(0, -y_offset);
  }

}
}  // namespace Engine
