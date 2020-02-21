#pragma once
#include "ImGuiHud.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace SoySoccer {
    //
    //
    //
class Window : public sf::RenderWindow {
   public:
    //
    //
    //
    Window(const std::string &title, const int width, const int height, int flags, bool fullscreen = false,
           const int in_fps = 60);
    //
    //
    //
    void Update();
    //
    //
    //
    static bool valid_video_mode(unsigned int width, unsigned int height);
protected:
    ImGuiHud hud;
};

}  // namespace SoySoccer
