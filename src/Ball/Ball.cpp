#include "Ball.hpp"
using namespace Engine;
//
//
//
Ball::Ball(Sprite &in_sprite, Sprite &in_shadow)
    : Entity(in_sprite, in_shadow) {
  // todo ball radius
  perspective_width = 6;
  collidable.setRadius(radius);
  movable.co_friction = 0.01F;
  movable.co_bounciness=0.8f;
}
//
//
//
void Ball::update() {
  Entity::Update();
  sprite.animate();
  collidable.setPosition(movable.position.x - collidable.getRadius(),
                         movable.position.y - collidable.getRadius());
}
