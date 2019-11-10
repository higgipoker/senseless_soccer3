#include "Picker.hpp"

#include "Engine/Collider.hpp"

#include <iostream>
namespace Engine {
//
//
//
Picker::Picker(sf::RenderWindow &in_window, std::set<Movable *> &in_movables)
    : window(in_window), movables(in_movables) {
}
//
//
//
void Picker::update() {
    if (dragging && grabbed) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
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
                if (Collider::contains(entity->getBounds(), worldPos)) {
                    std::cout << "Picked " << entity->name << std::endl;
                    dragging = true;
                    grabbed = entity;
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