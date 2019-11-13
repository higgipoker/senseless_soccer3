#include "Camera.hpp"

#include "Engine/Collider.hpp"

#include <algorithm>
#include <iostream>

namespace Engine {
//
//
//
Camera::Camera(float in_viewport_width, float in_viewport_height)
    : Entity(std::make_unique<Sprite>(), std::make_unique<Sprite>()),
      view{{0, 0, in_viewport_width, in_viewport_height}} {
    movable.toggleGravity(false);
    movable.properties.co_friction = 0.01F;
    speed = 2;
    collider.setRadius(100);
}
//
//
//
void Camera::follow(Entity &in_entity) {
    movable.position.x = in_entity.movable.position.x;
    movable.position.y = in_entity.movable.position.y;
    view.setCenter(movable.position.x, movable.position.y);
    following = &in_entity;
}
//
//
//
void Camera::update() {
    if (following) {
        Vector3 direction = following->movable.position - movable.position;
        float distance = direction.magnitude2d();
//        if (Math::greater_than(distance, 100)) {
        if(!Collider::contains(collider, following->movable.position)){
            direction.normalise();
            static const float speed_factor = 0.05F;
            static const float min_speed = 0;
            static const float max_speed = 8;
            float speed = std::clamp(distance * speed_factor, min_speed, max_speed);
            movable.velocity = direction * speed;
        }

        movable.velocity.to2d();
    }

    // constrain to world rect
    if (movable.position.x - view.getSize().x / 2 < world.left) {
        movable.setPosition(world.left + view.getSize().x / 2, movable.position.y);
    }
    if (movable.position.x + view.getSize().x / 2 > world.left + world.width) {
        movable.setPosition(world.left + world.width - view.getSize().x / 2, movable.position.y);
    }
    if (movable.position.y - view.getSize().y / 2 < world.top) {
        movable.setPosition(movable.position.x, world.top + view.getSize().y / 2);
    }
    if (movable.position.y + view.getSize().y / 2 > world.top + world.height) {
        movable.setPosition(movable.position.x, world.top + world.height - view.getSize().y / 2);
    }

    view.setCenter(movable.position.x, movable.position.y);
    collider.setCenter(view.getCenter());
}
//
//
//
sf::View &Camera::getview() {
    return view;
}
//
//
//
float Camera::getHeight() {
    return movable.position.z;
}
//
//
//
void Camera::setHeight(const float in_height) {
    movable.position.z = in_height;
}
//
//
//
void Camera::setWorldRect(sf::FloatRect in_rect) {
    world = in_rect;
}
}  // namespace Engine
