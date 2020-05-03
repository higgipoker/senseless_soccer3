#pragma once
#include "Debug.hpp"
#include "Entity.hpp"
//
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
//
#include <set>
namespace Senseless {
//
//
//
class Picker {
   public:
    //
    //
    //
    Picker(sf::RenderWindow &in_window, std::set<Entity *> &in_entities, Debug & in_debug);
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
    std::set<Entity *> &entities;
    bool dragging = false;
    Entity *grabbed = nullptr;
    sf::Vector2f last_dragged_position;
    bool hud_grabbed = false;
    sf::Vector2f grab_offset;
    Debug &debug;
};

}  // namespace Senseless
