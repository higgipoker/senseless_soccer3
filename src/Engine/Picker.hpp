#pragma once
#include "Movable.hpp"
//
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
//
#include <set>
namespace Engine {
//
//
//
class Picker {
   public:
    //
    //
    //
    Picker(sf::RenderWindow &in_window, std::set<Movable *> &in_movables);
    //
    //
    //
    void update();
    //
    //
    //
    void handleInput(const sf::Event &in_event);

private:
    sf::RenderWindow &window;
    std::set<Movable *> &movables;
    bool dragging = false;
    Movable* grabbed = nullptr;
    sf::Vector2f last_dragged_position;
};

}  // namespace Engine
