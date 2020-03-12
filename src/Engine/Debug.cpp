#include "Debug.hpp"

#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"

#include "Team/Team.hpp"

#include <SFML/Window/Event.hpp>

#include <iostream>

namespace Engine {
bool Debug::show_debug_hud = false;
bool Debug::flag_draw_bounds = false;
bool Debug::flag_draw_diagnostics = true;
float Debug::mini_map_scale_factor = 0.1F;
sf::Color Debug::bounds_color = sf::Color::Magenta;
sf::Color Debug::disgnostics_color = sf::Color::Green;
std::string Debug::picked;
int Debug::home_team_positioning = 0;
int Debug::away_team_positioning = 0;
int Debug::home_pitch_side = 0;
int Debug::away_pitch_side = 0;
int Debug::attacking_team = 0;

int Debug::active_team = 0;
Match *Debug::match = nullptr;
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
void Debug::draw(const int in_frames, const int in_frametime) {
    ImGui::SFML::Update(window, ui_clock.restart());
    ImGui::Begin("Debug");

    if (ImGui::CollapsingHeader("General", ImGuiTreeNodeFlags_DefaultOpen)) {
        // current frame
        { ImGui::Text("Frame: %i", in_frames - in_frames % 10); }
        // frametime
        { ImGui::Text("Frame time: %ims", in_frametime); }
        // mouse position
        {
            ImGui::Text("Mouse (screen): %i, %i", static_cast<int>(mouse_position.x),
                        static_cast<int>(mouse_position.y));
        }
        {
            ImGui::Text("Mouse (pitch): %i, %i", static_cast<int>(match->getPitch().toPitchSpace(mouse_position).x),
                        static_cast<int>(match->getPitch().toPitchSpace(mouse_position).x));
        }
        // draw bounds
        { ImGui::Checkbox("Draw Bounds", &flag_draw_bounds); }
        // draw diagnostics
        { ImGui::Checkbox("Draw Diagnostics", &flag_draw_diagnostics); }
        // picked entity
        { ImGui::Text("Picked : %s", picked.c_str()); }
    }
    if (ImGui::CollapsingHeader("Pitch")) {
        if (match) {
            // mouse pitch position
            auto p = match->getPitch().toPitchSpace({mouse_position.x, mouse_position.y});
            ImGui::Text("Pitch: %i, %i", static_cast<int>(p.x), static_cast<int>(p.y));
            // mini map scale factor
            match->getPitch().getMiniMapSprite().setScale(mini_map_scale_factor, mini_map_scale_factor);
            { ImGui::SliderFloat("", &mini_map_scale_factor, 0.1f, 0.5f, "radar = %.3f"); }
        }
    }
    if (ImGui::CollapsingHeader("Teams")) {
        int ori_attacking_team = attacking_team;
        ImGui::Text("Attacking Team");
        ImGui::RadioButton("Home", &attacking_team, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Away", &attacking_team, 1);
        if (ori_attacking_team != attacking_team) {
            match->setAttackingTeam(attacking_team == 0 ? TeamType::Home : TeamType::Away);
        }

        ImGui::Text("Set:");
        ImGui::SameLine();
        ImGui::RadioButton("Home Team", &active_team, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Away Team", &active_team, 1);
        draw_team_menu(active_team);
    }
    if (ImGui::CollapsingHeader("Players")) {
    }

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
        mouse_position.x = worldPos.x;
        mouse_position.y = worldPos.y;
    } else if (in_event.type == sf::Event::MouseWheelScrolled) {
        if (picked == "mini map") {
            mini_map_scale_factor += in_event.mouseWheelScroll.delta * 0.01F;
            mini_map_scale_factor = std::clamp(mini_map_scale_factor, 0.1F, 0.5F);
            match->getPitch().getMiniMapSprite().setScale(mini_map_scale_factor, mini_map_scale_factor);
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
//
//
//
void Debug::draw_team_menu(int which_team) {
    int *act_team_positioning = which_team == 0 ? &home_team_positioning : &away_team_positioning;
    int *act_pitch_side = which_team == 0 ? &home_pitch_side : &away_pitch_side;
    Team &act_team = which_team == 0 ? match->getHomeTeam() : match->getAwayTeam();

    int initial_positioning = *act_team_positioning;
    int initial_pitch_side = *act_pitch_side;
    ImGui::RadioButton("KickOff", act_team_positioning, 0);
    ImGui::RadioButton("GoalKick", act_team_positioning, 1);
    ImGui::RadioButton("Corner", act_team_positioning, 2);
    ImGui::RadioButton("Play", act_team_positioning, 9);

    ImGui::RadioButton("Left", act_pitch_side, 0);
    ImGui::SameLine();
    ImGui::RadioButton("Right", act_pitch_side, 1);

    Direction side = *act_pitch_side == 0 ? Direction::West : Direction::East;

    if (initial_positioning != *act_team_positioning || initial_pitch_side != *act_pitch_side) {
        switch (*act_team_positioning) {
            case 0:
                act_team.goToSetPiecePositions(Situation::KickOff);
                break;
            case 1:
                act_team.goToSetPiecePositions(Situation::GoalKick, side);
                break;
            case 2:
                act_team.goToSetPiecePositions(Situation::Corner, side);
                break;
            case 9:
                act_team.goToSetPiecePositions(Situation::Playing, side);
                break;
        }
    }
}
}  // namespace Engine
