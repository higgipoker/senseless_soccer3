#include "Entity.hpp"
//
#include "Metrics.hpp"
//
#include <cassert>
#include <iostream>
namespace Senseless {
GameState* Entity::gamestate = nullptr;
//
//
//
Entity::Entity(std::unique_ptr<Sprite> in_sprite, std::unique_ptr<Sprite> in_shadow)
    : renderable(std::move(in_sprite), std::move(in_shadow)) {
    // a sprite knows about its own shadow for perspectivizing
    renderable.sprite->shadow = renderable.shadow.get();
    // sprite needs to knwo the entity z for perspecitvizing
    renderable.sprite->entity_z = &movable.position.z;
}
//
//
//
void Entity::update(const float in_dt) {
    movable.step(in_dt);
    renderable.sprite->setPosition(movable.position.x, movable.position.y);
    renderable.shadow->setPosition({renderable.sprite->getPosition().x + SHADOW_OFFSET, renderable.sprite->getPosition().y + SHADOW_OFFSET});
    renderable.sprite->animate();
    renderable.sprite->z = static_cast<int>(movable.position.y);
    movable.setBounds(renderable.sprite->getGlobalBounds());
}
}  // namespace Senseless
