#pragma once
#include "Debug.hpp"
#include "Movable.hpp"
//
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
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
    Picker(sf::RenderWindow &in_window, std::set<Movable *> &in_movables, Debug & in_debug);
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
    Movable *grabbed = nullptr;
    sf::Vector2f last_dragged_position;
    bool hud_grabbed = false;
    sf::Vector2f grab_offset;
    Debug &debug;
};

}  // namespace Engine
