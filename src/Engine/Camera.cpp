#include "Camera.hpp"
//
#include "Engine/Collider.hpp"
//
#include <algorithm>
#include <iostream>

namespace Senseless {
//
//
//
Camera::Camera(float in_viewport_width, float in_viewport_height)
    : Entity(std::make_unique<Sprite>(), std::make_unique<Sprite>()),
      view{{0, 0, in_viewport_width, in_viewport_height}} {
    type = EntityType::Camera;
    movable.toggleGravity(false);
    movable.properties.co_friction = 0.01F;
    movable.speed = 5;
    collider.setRadius(200);
}
//
//
//
void Camera::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movable.velocity.y += -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movable.velocity.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movable.velocity.x += -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movable.velocity.x += 1;
    }
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
void Camera::update(const float in_dt) {
    Entity::update(in_dt);
    if (following) {
        movable.position.x = following->movable.position.x;
        movable.position.y = following->movable.position.y;
        view.setCenter(movable.position.x, movable.position.y);

    }

    // constrain to world rect
    if (movable.position.x - view.getSize().x / 2 < world.left) {
        movable.setPosition(world.left + view.getSize().x / 2, movable.position.y);
        movable.velocity.x = 0;
    }
    if (movable.position.x + view.getSize().x / 2 > world.left + world.width) {
        movable.setPosition(world.left + world.width - view.getSize().x / 2, movable.position.y);
        movable.velocity.x = 0;
    }
    if (movable.position.y - view.getSize().y / 2 < world.top) {
        movable.setPosition(movable.position.x, world.top + view.getSize().y / 2);
        movable.velocity.y = 0;
    }
    if (movable.position.y + view.getSize().y / 2 > world.top + world.height) {
        movable.setPosition(movable.position.x, world.top + world.height - view.getSize().y / 2);
        movable.velocity.y = 0;
    }

    view.setCenter(movable.position.x, movable.position.y);
    collider.setCenter(view.getCenter());
}
//
//
//
sf::View &Camera::getView() {
    return view;
}
//
//
//
sf::View &Camera::getHudView(){
    return hud_view;
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
//
//
//
sf::RectangleShape Camera::getRect(){
    sf::RectangleShape rect;

    rect.setPosition({view.getCenter().x - view.getSize().x/2,view.getCenter().y - view.getSize().y/2 });
    rect.setSize({view.getSize().x, view.getSize().y});

    return rect;
}
}  // namespace Senseless
