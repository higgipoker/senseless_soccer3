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
float Debug::mini_map_scale_factor = 0.1F;
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
    if (pitch) {
        // mouse pitch position
        auto p = pitch->toPitchSpace({mouse_x, mouse_y});
        ImGui::Text("Pitch: %i, %i", static_cast<int>(p.x), static_cast<int>(p.y));
        // mini map scale factor
        static_cast<MiniMap *>(&pitch->getMiniMap())->setScale(mini_map_scale_factor);
        { ImGui::SliderFloat("", &mini_map_scale_factor, 0.1f, 0.5f, "radar = %.3f"); }
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
