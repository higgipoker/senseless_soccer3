#pragma once
#include "Interact.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
namespace SoySoccer {
class ImGuiHud {
public:
    //
    //
    //
    ImGuiHud(sf::RenderWindow &win);
    //
    //
    //
    ~ImGuiHud();
    //
    //
    //
    void Show();
    //
    //
    //
    void HandleInput(const sf::Event &event);
    //
    bool shown = false;

private:
    sf::Clock ui_clock;
    sf::RenderWindow &window;
};

}  // namespace Hud
