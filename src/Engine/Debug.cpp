#include "Debug.hpp"

#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"

#include <SFML/Window/Event.hpp>

#include <iostream>

namespace Engine {
bool Debug::show_debug_hud = false;
bool Debug::flag_draw_bounds = false;
bool Debug::flag_draw_diagnostics = true;
Pitch *Debug::pitch = nullptr;
sf::Color Debug::bounds_color = sf::Color::Magenta;
sf::Color Debug::disgnostics_color = sf::Color::Green;
//
//
//
Debug::Debug(sf::RenderWindow &in_window) : window(in_window) {
    ImGui::SFML::Init(in_window);
}
//
//
//
Debug::~Debug() {
    ImGui::SFML::Shutdown();
}
//
//
//
void Debug::update(const int in_frames, const int in_frametime) {
    ImGui::SFML::Update(window, ui_clock.restart());
    ImGui::Begin("Debug");

    // current frame
    { ImGui::Text("Frame: %i", in_frames - in_frames % 10); }
    // frametime
    { ImGui::Text("Frame time: %ims", in_frametime); }
    // mouse position
    { ImGui::Text("Mouse: %i, %i", static_cast<int>(mouse_x), static_cast<int>(mouse_y)); }
    // mouse pitch position
    if (pitch) {
        auto p = pitch->toPitchSpace({mouse_x, mouse_y});
        ImGui::Text("Pitch: %i, %i", static_cast<int>(p.x), static_cast<int>(p.y));
    }
    // draw bounds
    { ImGui::Checkbox("Draw Bounds", &flag_draw_bounds); }
    // draw diagnostics
    { ImGui::Checkbox("Draw Diagnostics", &flag_draw_diagnostics); }

    ImGui::End();
    ImGui::SFML::Render(window);
}
//
//
//
void Debug::handleInput(sf::Event &in_event) {
    ImGui::SFML::ProcessEvent(in_event);

    if (in_event.type == sf::Event::MouseMoved) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
        mouse_x = worldPos.x;
        mouse_y = worldPos.y;
    }
    // handle mouse clicks
    if (in_event.type == sf::Event::MouseButtonPressed) {
        if (in_event.mouseButton.button == sf::Mouse::Left) {
            if (in_event.mouseButton.button == sf::Mouse::Left) {
                // get the current mouse position in the window
                //            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                // convert it to world coordinates
                //            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                //            std::cout << "click at " << static_cast<int>(worldPos.x) << ", " <<
                //            static_cast<int>(worldPos.y)
                //                      << std::endl;
                //      std::cout << "click at " << static_cast<int>(pixelPos.x) << ", "
                //                << static_cast<int>(pixelPos.y) << std::endl;
            }
        }
    }
}
//
//
//
void Debug::show() {
    show_debug_hud = true;
}
//
//
//
void Debug::toggle() {
    show_debug_hud = !show_debug_hud;
}
//
//
//
bool Debug::showHud() {
    return show_debug_hud;
}
//
//
//
bool Debug::drawBounds() {
    return flag_draw_bounds;
}
//
//
//
bool Debug::drawDiagnostics() {
    return flag_draw_diagnostics;
}
//
//
//
sf::Color Debug::defaultBoundsColor() {
    return bounds_color;
}
//
//
//
sf::Color Debug::defaultDiagnosticsColor() {
    return disgnostics_color;
}
}  // namespace Engine
