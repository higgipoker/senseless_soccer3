#include "Picker.hpp"

#include "Engine/Collider.hpp"

#include <iostream>
namespace Engine {
//
//
//
Picker::Picker(sf::RenderWindow &in_window, std::set<Movable *> &in_movables, Debug & in_debug)
    : window(in_window), movables(in_movables), debug(in_debug){
}
//
//
//
void Picker::update() {
    if (dragging && grabbed) {
        debug.picked = grabbed->name;
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
        if (hud_grabbed) {
            worldPos.x = static_cast<float>(pixelPos.x);
            worldPos.y = static_cast<float>(pixelPos.y);
        }
        worldPos.x -= grab_offset.x;
        worldPos.y -= grab_offset.y;
        grabbed->setPosition(worldPos);
        last_dragged_position = worldPos;
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

            for (auto &entity : movables) {
                if (entity->is_hud) {
                    if (Collider::contains(entity->getBounds(), pixelPos)) {
                        std::cout << "Picked " << entity->name << std::endl;
                        hud_grabbed = true;
                        dragging = true;
                        grabbed = entity;
                        grab_offset.x = pixelPos.x - entity->getBounds().left;
                        grab_offset.y = pixelPos.y - entity->getBounds().top;
                    }
                } else {
                    if (Collider::contains(entity->getBounds(), worldPos)) {
                        hud_grabbed = false;
                        std::cout << "Picked " << entity->name << std::endl;
                        dragging = true;
                        grabbed = entity;
                        grab_offset.x = 0;
                        grab_offset.y = 0;
                    }
                }
            }
        }
    } else if (in_event.type == sf::Event::MouseButtonReleased) {
        if (in_event.mouseButton.button == sf::Mouse::Left) {
            dragging = false;
            grabbed = nullptr;
        }
    }
}
}  // namespace Engine
