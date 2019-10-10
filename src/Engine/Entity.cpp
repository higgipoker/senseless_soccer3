#include "Entity.hpp"

#include "Metrics.hpp"

#include <iostream>
namespace Engine {
Sprite Entity::dummy_sprite;
Sprite Entity::dummy_shadow;
//
//
//
Entity::Entity() : sprite(dummy_sprite), shadow(dummy_shadow) {}
//
//
//
Entity::Entity(Sprite &in_sprite, Sprite &in_shadow)
    : sprite(in_sprite), shadow(in_shadow) {
  perspective_width = sprite.getLocalBounds().width;
}
//
//
//
void Entity::handleInput() {
  if (!input) return;

  if (input->up()) {
    movable.applyForce({0, -speed});
  }
  if (input->down()) {
    movable.applyForce({0, speed});
  }
  if (input->left()) {
    movable.applyForce({-speed, 0});
  }
  if (input->right()) {
    movable.applyForce({speed, 0});
  }
  if(input->fire_down()){
    movable.applyForce({0.F, 0.F, speed * 0.4F});
  }
}
//
//
//
void Entity::update() {
  sprite.setPosition(movable.getX(), movable.getY());
  shadow.setPosition(sprite.getPosition());
  shadow.move(shadow_offset, shadow_offset);
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

    // y offset due to height
    float z_cm = movable.getZ() * Metrics::Z_PERSP_OFFSET;
    if (Math::greater_than(z_cm, 0)) {
      float y_offset = Metrics::Y_OFFSET_DUE_TO_HEIGHT * z_cm;
      sprite.move(0, -y_offset);
    }
  }
}
//
//
//
void Entity::attachInput(InputDevice &in_device) { input = &in_device; }
//
//
//
void Entity::detachInput() { input = nullptr; }
//
//
//
InputDevice *Entity::getInput() const { return input; }
}  // namespace Engine
