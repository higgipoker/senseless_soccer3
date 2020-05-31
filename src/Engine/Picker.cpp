#include "Picker.hpp"

#include <iostream>

#include "Engine/Collider.hpp"
namespace Senseless {
//
//
//
Picker::Picker(const sf::RenderWindow &in_window, std::vector<Entity *> &in_entities, Debug &in_debug) : window(in_window), entities(in_entities), debug(in_debug) {
}
//
//
//
void Picker::update() {
    if (dragging && grabbed) {
        Debug::picked                 = grabbed;
        Debug::picked_position_screen = grabbed->movable.position;
        sf::Vector2i pixelPos         = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos         = window.mapPixelToCoords(pixelPos);
        if (hud_grabbed) {
            worldPos.x = static_cast<float>(pixelPos.x);
            worldPos.y = static_cast<float>(pixelPos.y);
        }
        worldPos.x -= grab_offset.x;
        worldPos.y -= grab_offset.y;
        grabbed->movable.setPosition(worldPos);
        last_dragged_position = worldPos;
        std::cout << worldPos.x << ", " << worldPos.y << std::endl;
    }
}
//
//
//
void Picker::handleInput(const sf::Event &in_event) {
    // handle mouse clicks
    if (in_event.type == sf::Event::MouseButtonPressed) {
        if (in_event.mouseButton.button == sf::Mouse::Left) {
            // get the current mouse position in the window
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            // convert it to world coordinates
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

            for (auto &entity : entities) {
                if (entity->movable.is_hud) {
                    if (Collider::contains(entity->movable.getBounds(), pixelPos)) {
                        std::cout << "Picked " << entity->name << std::endl;
                        hud_grabbed   = true;
                        dragging      = true;
                        grabbed       = entity;
                        grab_offset.x = pixelPos.x - entity->movable.getBounds().left;
                        grab_offset.y = pixelPos.y - entity->movable.getBounds().top;
                    }
                } else {
                    if (entity->type == EntityType::Pitch)
                        continue;
                    if (Collider::contains(entity->movable.getBounds(), worldPos)) {
                        hud_grabbed = false;
                        std::cout << "Picked " << entity->name << std::endl;
                        dragging      = true;
                        grabbed       = entity;
                        grab_offset.x = 0;
                        grab_offset.y = 0;
                    }
                }
            }
        }
    } else if (in_event.type == sf::Event::MouseButtonReleased) {
        if (in_event.mouseButton.button == sf::Mouse::Left) {
            dragging = false;
            grabbed  = nullptr;
        }
    }
}
}  // namespace Senseless
