#include "Ball.hpp"

#include <iostream>

#include "Engine/Debug.hpp"
#include <memory>
#include "Game/Game.hpp"
namespace Senseless {
//
//
//
Ball::Ball(std::unique_ptr<Sprite> in_sprite, std::unique_ptr<Sprite> in_shadow) : Entity(std::move(in_sprite), std::move(in_shadow)) {
    radius = 4.F;
    collidable.setRadius(radius);
    movable.properties.co_friction   = 0.01F;
    movable.properties.co_bounciness = 0.8F;
    movable.properties.cross_section = radius * 2;
    renderable.sprite->setBasePerspectiveWidth(radius * 2);
    renderable.shadow->setBasePerspectiveWidth(radius * 2);

    name = "ball";
}
//
//
//
void Ball::update(const float in_dt) {
    Entity::update(in_dt);
    if (recording_distance) {
        distance   = Vector::magnitude(movable.position - initial_position);
        float diff = Vector::magnitude(movable.position - last_position);
        if (Math::equal(Vector::magnitude2d(movable.velocity), 0.F) || Math::less_than(diff, 2.5F)) {
            recording_distance = false;
        }
        last_position = movable.position;
    }
    // update collidable object
    collidable.setCenter(movable.position.x, movable.position.y);

    // sprite only animates if moving
    if (Math::greater_than(Vector::magnitude(movable.velocity), 0)) {
        // sprite rotates in direction of movement (unless spin...later!!)
        const float offset = 180;  // TODO according to the spritesheet image
        renderable.sprite->setRotation(Vector::angle(movable.velocity) + offset);
        renderable.sprite->startAnimating();
    } else {
        renderable.sprite->stopAnimating();
    }
#ifndef NDEBUG
    collidable.setFillColor(sf::Color::Transparent);
    collidable.setOutlineThickness(1);
    collidable.setOutlineColor(Debug::defaultDiagnosticsColor());

    renderable.sprite->debug_shapes.clear();
    renderable.sprite->debug_shapes.push_back(&collidable);

    if (DRAW_RAYS) {
        xray.setSize({world.width, 1});
        xray.setPosition(0, collidable.getCenter().y);
        xray.setFillColor(sf::Color::Magenta);
        renderable.sprite->debug_shapes.push_back(&xray);

        yray.setSize({1, world.height});
        yray.setPosition(collidable.getCenter().x, 0);
        yray.setFillColor(sf::Color::Magenta);
        renderable.sprite->debug_shapes.push_back(&yray);
    }
#endif
}
//
//
//
void Ball::kick(sf::Vector3f in_force) {
    movable.resetForces();
    movable.resetVelocity();
    movable.applyForce(in_force);
    last_force = Vector::magnitude(in_force);
}
//
//
//
void Ball::applyTopSpin(float in_factor) {
    sf::Vector3f spin{0.F, 0.F, -in_factor};
    movable.forces.topspin += spin;
}
//
//
//
void Ball::applyBackSpin(float in_factor) {
}
//
//
//
void Ball::applySideSpin(sf::Vector3f in_spin) {
    // todo can't be spinning in opposite dirs at once
    movable.forces.sidespin += in_spin;
}
}  // namespace Senseless
