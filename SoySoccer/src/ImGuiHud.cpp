#include "ImGuiHud.hpp"
//
#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"
//
#include "Window.hpp"
namespace SoySoccer {
//
//
//
ImGuiHud::ImGuiHud(sf::RenderWindow &win) : window(win) {
    ImGui::SFML::Init(window);
}
//
//
//
ImGuiHud::~ImGuiHud() {
    ImGui::SFML::Shutdown();
}
//
//
//
void ImGuiHud::Show() {
    if (shown) {
        ImGui::SFML::Update(window, ui_clock.restart());
        ImGui::Begin("Debug");

        if (ImGui::CollapsingHeader("General", ImGuiTreeNodeFlags_DefaultOpen)) {
            // current frame
            { ImGui::Text("Frame"); }
            // draw bounds
            bool flag_draw_bounds = false;
            { ImGui::Checkbox("Draw Bounds", &flag_draw_bounds); }
        }

        ImGui::End();
        ImGui::SFML::Render(window);
    }
}
//
//
//
void ImGuiHud::HandleInput(const sf::Event &event) {
    if (shown) {
        ImGui::SFML::ProcessEvent(event);
    }
}
}  // namespace SoySoccer
